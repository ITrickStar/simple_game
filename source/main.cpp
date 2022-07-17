#include <iostream>
#include "../header/box.h"

int main()
{
    srand(time(0));
    box desc(30);
    std::cout << desc.fight();

    return 0;
}
