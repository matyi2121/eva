#include "gamemodel.h"

GameModel::GameModel(QString p1id,QString p2id, int Height, int Width)
    :height(Height),
      width(Width)
{
    fields.resize(height);
    for(int i = 0; i < height; ++i)
    {
        fields[i].resize(width);
        for(int j = 0; j < width; ++j)
        {
            fields[i][j] = Field::empty;
        }
    }
    players.resize(2);
    players[0] = new Player(p1id,start_p1,right);
    players[1] = new Player(p2id,start_p2,left);
}

GameModel::Collision GameModel::collision_check()const
{
    bool player_collides[players.size()];
    for(int i = 0; i < players.size(); ++i)
    {
        player_collides[i] = false;
    }

    Coord next_pos;
    for(int i = 0; i < players.size(); ++i)
    {
        next_pos = players[i]->get_pos()+players[i]->get_dir();
        if(is_wall(next_pos)
         ||is_player(next_pos))
        {
            player_collides[i] = true;
        }
    }

    //kihasznalva, hogy most csak 2 jatekos van
    Collision ret_val;
    if(player_collides[0] && player_collides[1])
    {
        ret_val = Collision::Both;
    }
    else if(player_collides[0])
    {
        ret_val = Collision::Player1;
    }
    else if(player_collides[1])
    {
        ret_val = Collision::Player2;
    }
    else
    {
        ret_val = Collision::None;
    }
    return ret_val;
}

bool GameModel::is_wall(Coord c)const
{
    return fields[c.y][c.x] == Field::wall
         || c.y == height
         || c.y == -1
         || c.x == width
         || c.x == -1;
}

bool GameModel::is_player(Coord c)const
{
    return fields[c.y][c.x] == Field::player1
         ||fields[c.y][c.x] == Field::player2;
}

void GameModel::next_round()
{
    QString player_id;
    Coord curr_pos;
    Coord dir;
    Coord next_pos;
    Collision coll;
    if((coll = collision_check()) == Collision::None)
    {
        for(int i = 0; i < players.size(); ++i)
        {
            player_id = players[i]->get_id();
            curr_pos = players[i]->get_pos();
            dir = players[i]->get_pos();
            next_pos = curr_pos + dir;

            players[i]->step();

            fields[curr_pos.y][curr_pos.x] = Field::wall;
            //refresh layout
            emit step(curr_pos, next_pos, player_id);
        }
    }
    else
    {
        emit collision(coll);
    }
}

GameModel::~GameModel()
{
    for(auto i : players)
        delete i;
}
