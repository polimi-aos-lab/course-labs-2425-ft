
#include <iostream>
#include "miosix.h"
#include "spi3polling.h"

using namespace std;
using namespace miosix;

int main()
{
    SPI3DriverPolling spi;
    using cs = Gpio<GPIOB_BASE,7>;
    cs::mode(Mode::OUTPUT); cs::high();
    for(;;)
    {
        cout << "Ready\n";
        string line;
        getline(cin,line);
        cs::low();
        spi.send(line.data(),line.size());
        cs::high();
    }
}