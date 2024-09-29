#include "DoorsControllingSystem.h"

const uint NUM_DOORS = 2;

int main()
{
    DoorsControllingSystem doorsControllingSystem{NUM_DOORS};
    doorsControllingSystem.initialize();
    doorsControllingSystem.run();
}
