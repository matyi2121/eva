#include "player.h"

Player::Player(int pid, Coord start_pos, Coord direction)
    :id(pid),
     pos(start_pos),
     dir(direction)
{

}

Coord Player::get_pos()const
{
    return pos;
}

Coord Player::get_dir()const
{
    return dir;
}

Coord Player::get_id()const
{
    return id;
}
