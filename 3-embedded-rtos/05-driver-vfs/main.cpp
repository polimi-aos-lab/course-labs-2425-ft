
#include <iostream>
#include <miosix.h>
#include <filesystem/file_access.h>
#include <filesystem/devfs/devfs.h>
#include "spi3dma.h"

using namespace std;
using namespace miosix;

class SPIDevice : public Device
{
public:
    SPIDevice() : Device(Device::STREAM), cs(Gpio<GPIOB_BASE,7>::getPin())
    {
        cs.mode(Mode::OUTPUT);
        cs.high();
    }

    virtual ssize_t writeBlock(const void *buffer, size_t size, off_t where)
    {
        cs.low();
        spi.send(reinterpret_cast<const char*>(buffer),size);
        cs.high();
        return size;
    }
    
    virtual ssize_t readBlock(void *buffer, size_t size, off_t where)
    {
        return -ENOTSUP; //Operation not supported by this driver
    }
    
    virtual int ioctl(int cmd, void *arg)
    {
        return -ENOTSUP; //Operation not supported by this driver
    }

private:
    SPI3DriverDma spi;
    GpioPin cs;
};

int main()
{
    FilesystemManager::instance().getDevFs()->addDevice("spiaos",intrusive_ref_ptr<Device>(new SPIDevice));
    
    //For simplicty we run this code in kernelspace, but vfs access can
    //cross the userspace/kernelspace barrier allowing userspace processes to
    //access our driver
    int spifd = open("/dev/spiaos", O_RDWR);
    if(spifd < 0) return 1;
    for(;;)
    {
        cout << "Ready\n";
        string line;
        getline(cin,line);
        write(spifd,line.data(),line.size());
    }
}
