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
    gm->change_dir('a');
    //jobbra megy es balra akarna menni
    QCOMPARE(gm->players[0]->dir,gm->right);
    //elso korben nem lehet iranyt valtoztatni
    gm->change_dir('w');
    QCOMPARE(gm->players[0]->dir,gm->right);
}

void gamemodeltest::cleanupTestCase()
{
    delete gm;
}

QTEST_APPLESS_MAIN(gamemodeltest)

#include "gamemodeltest.moc"

