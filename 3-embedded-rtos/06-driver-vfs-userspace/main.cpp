
#include <sys/wait.h>
#include <signal.h>
#include <spawn.h>
#include <miosix.h>
#include <filesystem/file_access.h>
#include <filesystem/devfs/devfs.h>
#include "spi3dma.h"

using namespace std;
using namespace miosix;

class SPIDevice : public Device
{
public:
    SPIDevice() : Device(Device::STREAM), cs(Gpio<PB,7>::getPin())
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

private:
    SPI3DriverDma spi;
    GpioPin cs;
};

int main()
{
    FilesystemManager::instance().getDevFs()->addDevice("spiaos",intrusive_ref_ptr<Device>(new SPIDevice));
    
    // Kernel-side program to start a userspace process
    pid_t pid;
    const char *arg[] = { "/bin/aos_userspace", nullptr };
    const char *env[] = { nullptr };
    int ec=posix_spawn(&pid,arg[0],NULL,NULL,(char* const*)arg,(char* const*)env);
    if(ec!=0)
    {
        iprintf("spawn returned %d\n",ec);
        return 1;
    }
    pid=wait(&ec);
    iprintf("pid %d exited\n",pid);
    if(WIFEXITED(ec))
    {
        iprintf("Exit code is %d\n",WEXITSTATUS(ec));
    } else if(WIFSIGNALED(ec)) {
        if(WTERMSIG(ec)==SIGSEGV) iprintf("Process segfaulted\n");
        else iprintf("Process terminated due to an error\n");
    }
    return 0;
}
