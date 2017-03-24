#ifndef PLAYER_H
#define PLAYER_H

struct Coord
{
    Coord(int X = 0, int Y = 0)
        :x(X),
         y(Y)
    {}
    int x;
    int y;
};

class Player
{
public:

    Player(int pid, Coord start_pos, Coord direction);
    Coord get_pos()const;
    Coord get_dir()const;
    Coord get_id()const;
private:
    int id;
    Coord pos;
    Coord dir;
};

#endif // PLAYER_H
