#include "gamemodel.h"
#include <QMessageBox>
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

    dir_p1 = right;
    dir_p2 = left;

    fields[start_p1.y][start_p1.x] = Field::player;
    fields[start_p2.y][start_p2.x] = Field::player;

    emit init_players(players[0]->get_id(),players[0]->get_pos(),players[0]->get_dir(),
                      players[1]->get_id(),players[1]->get_pos(),players[1]->get_dir());

    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(next_round()));
    timer->start(500);
}

void GameModel::change_dir(char button)
{
    if(toupper(button) == button && players[1]->first_round)
        return;
    else if(toupper(button) != button && players[0]->first_round)
        return;

    switch (button) {
    case 'w':
        players[0]->set_dir(up,dir_p1);
        break;
    case 'a':
        players[0]->set_dir(left,dir_p1);
        break;
    case 's':
        players[0]->set_dir(down,dir_p1);
        break;
    case 'd':
        players[0]->set_dir(right,dir_p1);
        break;
    case 'U':
        players[1]->set_dir(up,dir_p2);
        break;
    case 'L':
        players[1]->set_dir(left,dir_p2);
        break;
    case 'D':
        players[1]->set_dir(down,dir_p2);
        break;
    case 'R':
        players[1]->set_dir(right,dir_p2);
        break;
    default:
        timer->stop();
        QMessageBox qmsg;
        qmsg.setText(QObject::trUtf8("Press Ok, to resume the game."));
        qmsg.exec();

        emit set_focus();

        timer->start(500);
        break;
    }
}

GameModel::Collision GameModel::collision_check()const
{
    bool player_collides[players.size()];
    for(int i = 0; i < players.size(); ++i)
    {
        player_collides[i] = false;
    }
    //szamolhatod hogy hany hamis van
    //abbol kideritheto egybol, hogy 0 vagy mind utkozik
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
    return c.y >= height
         || c.x <= -1
         || c.y <= -1
         || c.x >= width
         || fields[c.y][c.x] == Field::wall;
}

bool GameModel::is_player(Coord c)const
{
    return fields[c.y][c.x] == Field::player;
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
            dir = players[i]->get_dir();
            next_pos = curr_pos + dir;

            players[i]->step();
            players[i]->first_round = false;

            fields[curr_pos.y][curr_pos.x] = Field::wall;
            fields[next_pos.y][next_pos.x] = Field::player;
            //refresh layout
            emit step(curr_pos, next_pos, player_id);
        }
        dir_p1 = players[0]->get_dir();
        dir_p2 = players[1]->get_dir();
    }
    else
    {
        emit collision(coll);
    }
}

GameModel::~GameModel()
{
    timer->stop();
    for(auto i : players)
        delete i;
}
