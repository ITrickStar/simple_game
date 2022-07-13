#include <random>
#include <string>

struct position
{
    int x, y;
    position(int _x, int _y) : x(_x), y(_y) {}

    position& operator=(int i)
    {
        x = i;
        y = i;
        return *this;
    }

    bool operator>(int input)
    {
        if (x > input || y > input)
            return true;
        return false;
    }
    bool operator<(int input)
    {
        if (x < 1 || y < 1)
            return true;
        return false;
    }

    bool operator==(position pos)
    {
        if (this->x == pos.x && this->y == pos.y)
            return true;
        return false;
    }
};

class creature
{
private:
    std::string name;

protected:
    int dmg;
    int speed;

public:
    int hp;
    position coord;

    creature(std::string _name = nullptr, int _hp = 0, int _dmg = 0, int _speed = 0) : name(_name), hp(_hp), dmg(_dmg), speed(_speed), coord(0, 0){};

    virtual position move(int);
    virtual void attack(creature &body) { body.hp -= this->dmg; }
    int getDmg() const { return dmg; }
    int getSpeed() const { return speed; }
    std::string getName() const { return name; }
};

position creature::move(int mapsize)
{
    position newpos = coord;
    for (int i = 0; i < speed; i++)
        if (rand() % 2)
            (rand() % 2) ? newpos.x++ : newpos.x--;
        else
            (rand() % 2) ? newpos.y++ : newpos.y--;

    if (newpos > mapsize || newpos < mapsize)
        newpos = move(mapsize);
    return newpos;
}

class rook : public creature
{
public:
    rook() : creature("rook", 2, 1, 1) {}
};

class bishop : public creature
{
public:
    bishop() : creature("bishop", 1, 2, 1) {}
};

class pawn : public creature
{
public:
    pawn() : creature("pawn", 1, 1, 2) {}
};
