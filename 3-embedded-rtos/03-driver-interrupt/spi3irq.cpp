
#include "spi3irq.h"

using namespace std;
using namespace miosix;

SPI3DriverIrq::SPI3DriverIrq()
{
    using sck  = Gpio<PB,3>;
    using miso = Gpio<PB,4>;
    using mosi = Gpio<PB,5>;
    {
        GlobalIrqLock dLock;
        sck::mode(Mode::ALTERNATE);  sck::alternateFunction(6);
        miso::mode(Mode::ALTERNATE); miso::alternateFunction(6);
        mosi::mode(Mode::ALTERNATE); mosi::alternateFunction(6);
        RCC->APB1ENR |= RCC_APB1ENR_SPI3EN; //Turn on SPI3 (clock gating)
        RCC_SYNC();
        IRQregisterIrq(dLock, SPI3_IRQn, &SPI3DriverIrq::interruptHandler, this);
    }
    SPI3->CR2 = SPI_CR2_RXNEIE;  //Enable interrupt on transfer complete
    SPI3->CR1 = SPI_CR1_SSM      //Handle CS in software
              | SPI_CR1_SSI      //Handle CS in software
              | SPI_CR1_SPE      //Enable peripheral
              | 4<<3             //42MHz / 32 = 1.3125MHz
              | SPI_CR1_MSTR;    //Master mode
}

void SPI3DriverIrq::send(const char *data, int size)
{
    if(size <= 0) return;
    unique_lock<mutex> l(m);
    GlobalIrqLock dLock;
    this->data = data;
    this->size = size;
    this->index = 0;
    SPI3->DR = data[index++];
    waiting = Thread::IRQgetCurrentThread();
    while(waiting) Thread::IRQglobalIrqUnlockAndWait(dLock);
}

SPI3DriverIrq::~SPI3DriverIrq()
{
    GlobalIrqLock dLock;
    IRQunregisterIrq(dLock, SPI3_IRQn, &SPI3DriverIrq::interruptHandler, this);
}

void SPI3DriverIrq::interruptHandler()
{
    FastGlobalLockFromIrq dLock;
    volatile int ignored = SPI3->DR; //"consume" received byte and ignore it
    (void)ignored;
    if(index < size)
    {
        SPI3->DR = data[index++];
    } else if(waiting) {
        waiting->IRQwakeup();
        waiting = nullptr;
    }
}
