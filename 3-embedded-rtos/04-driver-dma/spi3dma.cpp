
#include "spi3dma.h"

using namespace std;
using namespace miosix;

SPI3DriverDma::SPI3DriverDma()
{
    using sck  = Gpio<GPIOB_BASE,3>;
    using miso = Gpio<GPIOB_BASE,4>;
    using mosi = Gpio<GPIOB_BASE,5>;
    {
        FastInterruptDisableLock dLock;
        sck::mode(Mode::ALTERNATE);  sck::alternateFunction(6);
        miso::mode(Mode::ALTERNATE); miso::alternateFunction(6);
        mosi::mode(Mode::ALTERNATE); mosi::alternateFunction(6);
        RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN; //Turn on DMA1 (clock gating)
        RCC->APB1ENR |= RCC_APB1ENR_SPI3EN; //Turn on SPI3 (clock gating)
        RCC_SYNC();
    }
    SPI3->CR2 = SPI_CR2_TXDMAEN; //Enable DMA
    SPI3->CR1 = SPI_CR1_SSM      //Handle CS in software
              | SPI_CR1_SSI      //Handle CS in software
              | SPI_CR1_SPE      //Enable peripheral
              | 4<<3             //42MHz / 32 = 1.3125MHz
              | SPI_CR1_MSTR;    //Master mode
    IRQregisterIrq(DMA1_Stream5_IRQn, &SPI3DriverDma::interruptHandler, this);
    NVIC_SetPriority(DMA1_Stream5_IRQn, 15);
    NVIC_EnableIRQ(DMA1_Stream5_IRQn);
}

SPI3DriverDma::~SPI3DriverDma()
{
    NVIC_DisableIRQ(DMA1_Stream5_IRQn);
    IRQunregisterIrq(DMA1_Stream5_IRQn);
}

void SPI3DriverDma::send(const char *data, int size)
{
    if(size <= 0) return;
    unique_lock<mutex> l(m);
    {
        FastInterruptDisableLock dLock;
        DMA1_Stream5->CR = 0;
        DMA1_Stream5->PAR  = reinterpret_cast<unsigned int>(&SPI3->DR);
        DMA1_Stream5->M0AR = reinterpret_cast<unsigned int>(data);
        DMA1_Stream5->NDTR = size;
        DMA1_Stream5->CR = DMA_SxCR_MINC  //Increment memory pointer
                         | DMA_SxCR_DIR_0 //Memory to peripheral
                         | DMA_SxCR_TCIE  //Interrupt on transfer complete
                         | DMA_SxCR_TEIE  //Interrupt on transfer error
                         | DMA_SxCR_DMEIE //Interrupt on direct mode error
                         | DMA_SxCR_EN;   //Start DMA
        waiting = Thread::getCurrentThread();
        while(waiting) Thread::IRQenableIrqAndWait(dLock);
    }
    //Hardware-specific quirk: the DMA end of transfer interrupt in the STM32
    //microcontroller is sent when the last byte is *beginning* to be sent, not
    //when it has *finished* sending. This quirk only occurs when enabling DMA
    //for send-only and would not happen if we were also receiving. To work
    //around this quirk we use polling to wait for the last byte to be sent.
    //When sending large buffers the impact is minimal.
    while(SPI3->SR & SPI_SR_BSY) ;
}

void SPI3DriverDma::interruptHandler()
{
    DMA1->HIFCR = DMA_HIFCR_CTCIF5
                | DMA_HIFCR_CTEIF5
                | DMA_HIFCR_CDMEIF5;
    if(waiting)
    {
        waiting->IRQwakeup();
        if(waiting->IRQgetPriority()>Thread::IRQgetCurrentThread()->IRQgetPriority())
            IRQinvokeScheduler();
        waiting = nullptr;
    }
}
