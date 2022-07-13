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
        for (j + 1; j < plcount; j++)
            player[j] = player[j - 1];
        plcount--;
    }

    creature fight()
    {
        while (plcount > 1)
            for (int i = 0; i < plcount; i++)
            {
                position nextmove = player[i].move(mapsize);
                std::string ame = player[i].getName(); 
                bool atk;
                for (int j = 0; j < plcount; j++)
                {

                    if (i != j && nextmove == player[j].coord)
                    {
                        player[i].attack(player[j]);
                        if (player[j].hp <= 0)
                            kill(j);
                        atk = true;
                        break;
                    }
                }
                if (!atk)
                    player[i].coord = nextmove;
            }
        return *player;
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
    for (int i = 1; i < plcount; i++)
    {
        player[i].coord = i;
    }
}

box::~box() { delete[] player; }

// поле есть двумерный массив указателей на объекты
// очередность ходов - позиции элементов в этом массиве
// для перемещения используются встроенные методы объектов
