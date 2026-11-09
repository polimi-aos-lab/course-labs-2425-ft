
#include <iostream>
#include "miosix.h"
#include "spi3irq.h"

using namespace std;
using namespace miosix;

int main()
{
    SPI3DriverIrq spi;
    using cs = Gpio<PB,7>;
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
