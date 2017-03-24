#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include <QVector>
#include "player.h"

class GameModel : public QObject
{
    Q_OBJECT
public:
    enum class Collision
    {
        Player1,
        Player2,
        Both,
        None
    };
    enum class Field
    {
        empty = -1,
        wall = 0,
        player1 = 1,
        player2 = 2,
    };

    GameModel(QString p1id,QString p2id,int Height, int Width);
    ~GameModel();
private:
    QVector<Player*> players;
    QVector<QVector<Field> > fields;
    int height;
    int width;

    Coord right = Coord(1,0);
    Coord left = Coord(-1,0);
    Coord up = Coord(0,-1);
    Coord down = Coord(0,1);

    Coord start_p1 = Coord(0,height/2);
    Coord start_p2 = Coord(width-1,height/2);

    Collision collision_check()const;
    bool is_wall(Coord c)const;
    bool is_player(Coord c)const;
signals:
    void collision(Collision);
    //prev_pos curr_pos player_id
    void step(Coord,Coord,QString);
public slots:
    void next_round();//timer hivja majd meg
};

#endif // GAMEMODEL_H
