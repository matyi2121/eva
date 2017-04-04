#include <QString>
#include "gamemodel.h"
#include <QtTest>

class gamemodeltest : public QObject
{
    Q_OBJECT

public:
    gamemodeltest();
    GameModel* gm;
private Q_SLOTS:
    void initTestCase();
    void is_wall();
    void is_player();
    void changeDirTest();
    void collisionTest();
    void cleanupTestCase();
};

gamemodeltest::gamemodeltest()
{
}
void gamemodeltest::initTestCase()
{
    gm = new GameModel("p1","p2",12,12);
}
void gamemodeltest::is_wall()
{
    QCOMPARE(gm->is_wall(Coord(100,100)),true);
    QCOMPARE(gm->is_wall(Coord(3,3)),false);
}

void gamemodeltest::is_player()
{
    QCOMPARE(gm->is_player(Coord(0,0)),false);
    QCOMPARE(gm->is_player(Coord(gm->width-1,gm->height/2)),true);
}

void gamemodeltest::changeDirTest()
{
    gm->change_dir('d');
    QCOMPARE(gm->players[0]->dir,gm->right);

    //jobbra megy es balra akarna menni
    gm->change_dir('a');
    QCOMPARE(gm->players[0]->dir,gm->right);

    //elso korben nem lehet iranyt valtoztatni
    gm->change_dir('w');
    QCOMPARE(gm->players[0]->dir,gm->right);

    gm->players[0]->first_round = false;
    gm->change_dir('w');
    QCOMPARE(gm->players[0]->dir,gm->up);
    gm->players[0]->first_round = true;
}

void gamemodeltest::collisionTest()
{
    gm->players[0]->dir = gm->right;
    gm->players[1]->dir = gm->left;

    QCOMPARE(gm->collision_check(),GameModel::Collision::None);

    gm->fields[gm->players[0]->pos.y][gm->players[0]->pos.x] = GameModel::Field::empty;
    gm->fields[gm->players[1]->pos.y][gm->players[1]->pos.x] = GameModel::Field::empty;
    gm->fields[0][0] = GameModel::Field::player;
    gm->fields[0][1] = GameModel::Field::player;

    gm->players[0]->pos = Coord(0,0);
    gm->players[1]->pos = Coord(1,0);
    QCOMPARE(gm->collision_check(),GameModel::Collision::Both);

    gm->fields[gm->players[0]->pos.y][gm->players[0]->pos.x] = GameModel::Field::empty;
    gm->fields[gm->players[1]->pos.y][gm->players[1]->pos.x] = GameModel::Field::empty;
    gm->fields[0][11] = GameModel::Field::player;
    gm->fields[3][4] = GameModel::Field::player;

    gm->players[0]->pos = Coord(11,0);
    gm->players[1]->pos = Coord(4,3);
    QCOMPARE(gm->collision_check(),GameModel::Collision::Player1);
}

void gamemodeltest::cleanupTestCase()
{
    delete gm;
}

QTEST_APPLESS_MAIN(gamemodeltest)

#include "gamemodeltest.moc"

