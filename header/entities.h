// структура описывающая позицию фигуры
struct position
{
    int x, y;
    position(int _x, int _y) : x(_x), y(_y) {}

    position &operator=(int i)
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

    friend std::ostream &operator<<(std::ostream &out, position input);
};
std::ostream &operator<<(std::ostream &out, position input)
{
    out << '[' << input.x << ", " << input.y << ']';

    return out;
}

// класс-предок
// не придумал как его сделать чисто виртуальным или интерфейсом
class creature
{
private:
    std::string name;

protected:
    int dmg;
    int speed;
    position coord;

public:
    int hp; // сделал публичным, тк поле легче менять напрямую

    creature(std::string _name = nullptr, int _hp = 0, int _dmg = 0, int _speed = 0) : name(_name), hp(_hp), dmg(_dmg), speed(_speed), coord(0, 0){};

    virtual position move(int);
    virtual void attack(creature &body);
    int getDmg() const { return dmg; }
    int getSpeed() const { return speed; }
    position getCoord() const { return coord; }
    void setCoord(int key) { coord = key; }
    void setCoord(position key) { coord = key; }
    std::string getName() const { return name; }
};

// метод получает ссылку на объект и вычитает из его hp параметр dmg
// также выводит действие в консоль
// мог бы конечно придумать что интереснее
void creature::attack(creature &body)
{
    body.hp -= this->dmg;
    std::cout << this->getName() << " attacked " << body.getName() << std::endl;
}

// просто увеличивает или уменьшает случайный параметр
// возвращает следующую позицию, но не присваетвает его полю
position creature::move(int mapsize)
{
    position newpos = coord;
    for (int i = 0; i < speed; i++)
    {
        if (rand() % 2)
            (rand() % 2) ? newpos.x++ : newpos.x--;
        else
            (rand() % 2) ? newpos.y++ : newpos.y--;
        if (newpos > mapsize || newpos < mapsize)
            newpos = move(mapsize);
    }

    return newpos;
}

// пока классы-наследники отличаются только параметрами
// попробую переопределить для них методы
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
