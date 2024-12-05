
#include "active_object.h"

using namespace std;

ActiveObject::ActiveObject() : quit(false), t(&ActiveObject::run, this) {}

ActiveObject::~ActiveObject()
{
    if(quit.load()) return; //For derived classes
    quit.store(true);
    t.join();
}
