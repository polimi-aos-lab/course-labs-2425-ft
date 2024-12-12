
#pragma once

#include <mutex>
#include <miosix.h>

class SPI3DriverDma
{
public:
    SPI3DriverDma();

    void send(const char *data, int size);
    
    ~SPI3DriverDma();

    SPI3DriverDma(const SPI3DriverDma&) = delete;
    SPI3DriverDma& operator= (const SPI3DriverDma&) = delete;

private:
    void interruptHandler();

    std::mutex m;
    miosix::Thread *waiting = nullptr;
};
