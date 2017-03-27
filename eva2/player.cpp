#include "player.h"

Player::Player(QString pid, Coord start_pos, Coord direction)
    :id(pid),
     pos(start_pos),
     dir(direction)
{
    changed_this_round = true;
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

bool Player::set_dir(Coord Dir)
{
    if(dir == Dir)
    {
        return false;
    }
    if(dir != -1*Dir)
    {
        dir = Dir;
    }
    return true;
}

void Player::step()
{
    pos = pos + dir;
}
