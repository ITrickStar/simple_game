// поле отрисовывается отдельно
// очередность ходов - позиции элементов в этом массиве
// для перемещения используются внутренние методы объектов


#include "entities.h"

// класс реализующий поле где происходит игра
class box
{
private:
    int mapsize;
    int plcount;
    creature *players; // массив с "игроками"

    void arrange(); // размещает фигуры на доске, используется в конструкторе
    void print(); // выводит поле в консоль, плохо оптимизирована
    void kill(int, int); // удаляет убитого игрока с поля

public:
    box(int);
    ~box();

    std::string fight(); // этот метод и есть сама игра
};

void box::arrange()
{
    for (int i = 0; i < plcount; i++)
    {
        players[i].setCoord((rand() % mapsize) + 1);
        auto mem = players[i].getCoord();
    }
    for (int j = 0; j < plcount; j++)
    {
        for (int i = 0; i < plcount; i++)
        {
            if (players[j].getCoord() == players[i].getCoord() && i != j)
            {
                players[i].setCoord((rand() % (mapsize)) + 1);
                j--;
                break;
            }
        }
        auto mem = players[j].getCoord();
    }
}

// вроде вынес основные вычисления, но все равно выглядит громоздко
box::box(int size)
{
    mapsize = size;
    plcount = 3;
    if (plcount > mapsize || mapsize <= 0)
        throw("error"); // опять использую без try/catch,
                        // он здесь сугубо чтобы программа вылетела
    rook pl1;   // наверное добавление объектов можно сделать лучше
    bishop pl2;
    pawn pl3;
    players = new creature[plcount]{pl1, pl2, pl3};
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
            position nextmove = players[i].move(mapsize);
            bool atk = false;
            for (int j = 0; j < plcount; j++)
            {

                if (i != j && nextmove == players[j].getCoord())
                {
                    players[i].attack(players[j]);
                    atk = true;
                    if (players[j].hp <= 0)
                        kill(i, j);
                    break;
                }
            }
            if (!atk)
            {
                std::cout << players[i].getName() << ": " << players[i].getCoord() << " -> " << nextmove << std::endl;
                players[i].setCoord(nextmove);
            }
        }

        print();
    }
    std::cout << "turns: " << turns - 1 << "; winner: ";
    return players->getName();
}

void box::kill(int murder, int victim)
{
    std::cout << players[murder].getName() << " killed " << players[victim].getName() << std::endl;
    for (int j = victim; j < plcount - 1; j++)
        players[j] = players[j + 1];
    plcount--;
}

// не знаю что придумать лучше кроме сравнивать позиции объектов и номер клетки
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
                if (j == players[p].getCoord().x && i == players[p].getCoord().y)
                {
                    std::cout << players[p].getName()[0];
                    f = false;
                }
            if (f)
                std::cout << ' ';
        }
        std::cout << '|' << std::endl;
    }
    std::cout << std::endl;
}

box::~box() { delete[] players; }
