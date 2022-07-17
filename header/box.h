#include "entities.h"
#include <iostream>

class box
{
private:
    int mapsize;
    int plcount;
    creature *player;

    void arrange()
    {
        for (int i = 0; i < plcount; i++)
        {
            player[i].setCoord((rand() % mapsize) + 1);
            auto mem = player[i].getCoord();
        }
        for (int j = 0; j < plcount; j++)
        {
            for (int i = 0; i < plcount; i++)
            {
                if (player[j].getCoord() == player[i].getCoord() && i != j)
                {
                    player[i].setCoord((rand() % (mapsize)) + 1);
                    j--;
                    break;
                }
            }
            auto mem = player[j].getCoord();
        }
    }

public:
    box(int);
    ~box();

    void print();
    void kill(int murder, int victim)
    {
        std::cout << player[murder].getName() << " killed " << player[victim].getName() << std::endl;
        for (int j = victim; j < plcount - 1; j++)
            player[j] = player[j + 1];
        plcount--;
    }

    std::string fight();
};

box::box(int size)
{
    mapsize = size;
    plcount = 3;
    if (plcount > mapsize)
        throw("error");
    rook pl1;
    bishop pl2;
    pawn pl3;
    player = new creature[plcount]{pl1, pl2, pl3};
    arrange();
}

std::string box::fight()
{
    int turns = 0;
    while (plcount > 1)
    {
        for (int i = 0; i < plcount; i++)
        {
            position nextmove = player[i].move(mapsize);
            creature ame = player[i];
            bool atk = false;
            for (int j = 0; j < plcount; j++)
            {

                if (i != j && nextmove == player[j].getCoord())
                {
                    player[i].attack(player[j]);
                    if (player[j].hp <= 0)
                        kill(i, j);
                    atk = true;
                    break;
                }
            }
            if (!atk)
                player[i].setCoord(nextmove);
        }
        turns++;
    }
    std::cout << turns << " winner ";
    return player->getName();
}

void box::print()
{
    
}

box::~box() { delete[] player; }

// поле есть двумерный массив указателей на объекты
// очередность ходов - позиции элементов в этом массиве
// для перемещения используются встроенные методы объектов
