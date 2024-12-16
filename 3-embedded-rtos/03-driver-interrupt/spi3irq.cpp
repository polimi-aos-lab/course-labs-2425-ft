
#include "spi3irq.h"

using namespace std;
using namespace miosix;

SPI3DriverIrq::SPI3DriverIrq()
{
    using sck  = Gpio<GPIOB_BASE,3>;
    using miso = Gpio<GPIOB_BASE,4>;
    using mosi = Gpio<GPIOB_BASE,5>;
    {
        FastInterruptDisableLock dLock;
        sck::mode(Mode::ALTERNATE);  sck::alternateFunction(6);
        miso::mode(Mode::ALTERNATE); miso::alternateFunction(6);
        mosi::mode(Mode::ALTERNATE); mosi::alternateFunction(6);
        RCC->APB1ENR |= RCC_APB1ENR_SPI3EN; //Turn on SPI3 (clock gating)
        RCC_SYNC();
    }
    SPI3->CR2 = SPI_CR2_RXNEIE;  //Enable interrupt on transfer complete
    SPI3->CR1 = SPI_CR1_SSM      //Handle CS in software
              | SPI_CR1_SSI      //Handle CS in software
              | SPI_CR1_SPE      //Enable peripheral
              | 4<<3             //42MHz / 32 = 1.3125MHz
              | SPI_CR1_MSTR;    //Master mode
    IRQregisterIrq(SPI3_IRQn, &SPI3DriverIrq::interruptHandler, this);
}

void SPI3DriverIrq::send(const char *data, int size)
{
    if(size <= 0) return;
    unique_lock<mutex> l(m);
    FastInterruptDisableLock dLock;
    this->data = data;
    this->size = size;
    this->index = 0;
    SPI3->DR = data[index++];
    waiting = Thread::IRQgetCurrentThread();
    while(waiting) Thread::IRQenableIrqAndWait(dLock);
}

void SPI3DriverIrq::interruptHandler()
{
    volatile int ignored = SPI3->DR; //"consume" received byte and ignore it
    if(index < size)
    {
        SPI3->DR = data[index++];
    } else if(waiting) {
        waiting->IRQwakeup();
        waiting = nullptr;
    }
}
