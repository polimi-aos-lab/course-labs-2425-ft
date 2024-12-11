
#include "spi3polling.h"
#include <miosix.h>

using namespace miosix;

SPI3DriverPolling::SPI3DriverPolling()
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
    SPI3->CR1 = SPI_CR1_SSM      //Handle CS in software
              | SPI_CR1_SSI      //Handle CS in software
              | SPI_CR1_SPE      //Enable peripheral
              | 4<<3             //42MHz / 32 = 1.3125MHz
              | SPI_CR1_MSTR;    //Master mode
}

void SPI3DriverPolling::send(const char *data, int size)
{
    for(int i = 0; i < size; i++)
    {
        SPI3->DR = data[i];
        while((SPI3->SR & SPI_SR_RXNE)==0) ; //Polling loop
        volatile int ignored = SPI3->DR; //"consume" received byte and ignore it
    }
}
