#include <iostream>
#include <random>
#include <string>
#include "../header/box.h"

// можно было запустить все в одну функцию, но оставил так
// вроде работает для поля любого размера и даже заканчивается
int main()
{
    srand(time(0));
    box desc(10); // передаваемое значение - размер поля
    std::cout << desc.fight();

    return 0;
}
