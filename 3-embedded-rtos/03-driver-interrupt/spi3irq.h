
#pragma once

#include <mutex>
#include <miosix.h>

class SPI3DriverIrq
{
public:
    SPI3DriverIrq();

    void send(const char *data, int size);
    
    ~SPI3DriverIrq() { miosix::IRQunregisterIrq(SPI3_IRQn); }

    SPI3DriverIrq(const SPI3DriverIrq&) = delete;
    SPI3DriverIrq& operator= (const SPI3DriverIrq&) = delete;

private:
    void interruptHandler();

    std::mutex m;
    miosix::Thread *waiting = nullptr;
    const char *data;
    int size;
    int index;
};
