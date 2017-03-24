#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QVector>
#include "player.h"

class GameModel
{
public:
    enum class Collision
    {
        Player1,
        Player2,
        Both
    };
    enum class Field
    {
        empty = -1,
        player1wall = 0,
        player1 = 1,
        player2 = 2,
        player2wall = 3
    };

    GameModel(int Height, int Width);
private:
    QVector<Player> players;
    QVector<QVector<Field> > fields;
    int height;
    int width;
};

#endif // GAMEMODEL_H
