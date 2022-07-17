#include "entities.h"
#include <iostream>

class box
{
private:
    int mapsize;
    int plcount = 3;
    creature *player;

public:
    box(int);
    ~box();

    void kill(int j)
    {
        std::cout << "player killed " << player[j].getName() << std::endl;
        for (j; j < plcount - 1; j++)
            player[j] = player[j + 1];
        plcount--;
    }

    std::string fight()
    {
        while (plcount > 1)
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
                            kill(j);
                        atk = true;
                        break;
                    }
                }
                if (!atk)
                    player[i].setCoord(nextmove);
            }
        return player->getName();
    }
};

box::box(int size)
{
    mapsize = size;
    if (plcount > mapsize)
        throw("error");
    rook pl1;
    bishop pl2;
    pawn pl3;
    player = new creature[plcount]{pl1, pl2, pl3};
    for (int i = 0; i < plcount; i++)
    {
        player[i].setCoord(i + 1);
    }
}

box::~box() { delete[] player; }

// поле есть двумерный массив указателей на объекты
// очередность ходов - позиции элементов в этом массиве
// для перемещения используются встроенные методы объектов
