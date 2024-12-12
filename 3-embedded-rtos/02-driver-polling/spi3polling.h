
#pragma once

#include <mutex>

class SPI3DriverPolling
{
public:
    SPI3DriverPolling();

    void send(const char *data, int size);

    SPI3DriverPolling(const SPI3DriverPolling&) = delete;
    SPI3DriverPolling& operator= (const SPI3DriverPolling&) = delete;
    
private:
    std::mutex m;
};
