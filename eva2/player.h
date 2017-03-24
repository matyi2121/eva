#ifndef PLAYER_H
#define PLAYER_H
#include<QString>
struct Coord
{
    Coord(int X = 0, int Y = 0)
        :x(X),
         y(Y)
    {}
    friend inline Coord operator+(Coord a, Coord b)
    {
        return Coord(a.x+b.x, a.y+b.y);
    }
    friend inline Coord operator-(Coord a, Coord b)
    {
        return Coord(a.x-b.x, a.y-b.y);
    }
    int x;
    int y;
};

class Player
{
public:

    Player(QString pid, Coord start_pos, Coord direction);
    Coord get_pos()const;
    Coord get_dir()const;
    QString get_id()const;
    void set_dir(Coord dir);
    void step();
private:
    QString id;
    Coord pos;
    Coord dir;
};

#endif // PLAYER_H
