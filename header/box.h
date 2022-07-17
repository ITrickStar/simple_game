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
    int turns = 1;
    while (plcount > 1)
    {
        std::cout << "turn: " << turns++ << std::endl;
        for (int i = 0; i < plcount; i++)
        {
            position nextmove = player[i].move(mapsize);
            bool atk = false;
            for (int j = 0; j < plcount; j++)
            {

                if (i != j && nextmove == player[j].getCoord())
                {
                    player[i].attack(player[j]);
                    atk = true;
                    if (player[j].hp <= 0)
                        kill(i, j);
                    break;
                }
            }
            if (!atk)
            {
                std::cout << player[i].getName() << ": " << player[i].getCoord() << " -> " << nextmove << std::endl;
                player[i].setCoord(nextmove);
            }
        }

        print();
    }
    std::cout << "turns: " << turns-1 << "; winner: ";
    return player->getName();
}

void box::print()
{
    bool f;
    for (int i = 1; i < mapsize + 1; i++)
    {
        for (int j = 1; j < mapsize + 1; j++)
        {
            std::cout << '|';
            f = true;
            for (int p = 0; p < plcount; p++)
                if (j == player[p].getCoord().x && i == player[p].getCoord().y)
                {
                    std::cout << player[p].getName()[0];
                    f = false;
                }
            if (f)
                std::cout << ' ';
        }
        std::cout << '|' << std::endl;
    }
    std::cout << std::endl;
}

box::~box() { delete[] player; }

// поле есть двумерный массив указателей на объекты
// очередность ходов - позиции элементов в этом массиве
// для перемещения используются встроенные методы объектов
