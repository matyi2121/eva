#include "player.h"

Player::Player(QString pid, Coord start_pos, Coord direction)
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

QString Player::get_id()const
{
    return id;
}

void Player::set_dir(Coord Dir)
{
    dir = Dir;
}

void Player::step()
{
    pos = pos + dir;
}
