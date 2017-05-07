#include <QString>
#include <QtTest>
#include <QDebug>
#include "gamemodel.h"
#include "resourcemanager_mock.h"
class Eva3_unittest_mock : public QObject
{
    Q_OBJECT

public:
    Eva3_unittest_mock();
    ResourceManager* rm;
    GameModel* gm;
private Q_SLOTS:
    void initTestCase();
    void testNewGame();
    void testStep();
    void testLoadGame();
    void testWillComeAgain();
    void testSaveGame();
    void cleanupTestCase();
};

Eva3_unittest_mock::Eva3_unittest_mock()
{
}

void Eva3_unittest_mock::initTestCase()
{
    rm = new ResourceManager_Mock;
    gm = new GameModel(rm,4);
}

void Eva3_unittest_mock::testNewGame()
{
    QCOMPARE(gm->get_collector(Field::Blue),0);
    QCOMPARE(gm->get_collector(Field::Red),0);
    for(int i = 1; i < 5; ++i)
    {
        QCOMPARE(gm->get_field(Field::Blue,i),6);
        QCOMPARE(gm->is_empty(0,i),false);
        QCOMPARE(gm->get_field(Field::Red,i),6);
        QCOMPARE(gm->is_empty(1,i),false);
    }
    QCOMPARE(gm->players_turn(Field::Blue),true);
}

void Eva3_unittest_mock::testStep()
{
    gm->empty(0,1);//kek elsore click
    QCOMPARE(gm->get_collector(Field::Blue),0);
    QCOMPARE(gm->get_field(Field::Blue,1),0);
    QCOMPARE(gm->get_field(Field::Blue,2),7);
    QCOMPARE(gm->get_field(Field::Blue,3),7);
    QCOMPARE(gm->get_field(Field::Blue,4),7);
    QCOMPARE(gm->get_collector(Field::Red),1);
    QCOMPARE(gm->get_field(Field::Red,1),6);
    QCOMPARE(gm->get_field(Field::Red,2),6);
    QCOMPARE(gm->get_field(Field::Red,3),7);
    QCOMPARE(gm->get_field(Field::Red,4),7);

    QCOMPARE(gm->players_turn(Field::Red),true);
}

void Eva3_unittest_mock::testLoadGame()
{
    QCOMPARE(gm->load_game(),true);
}

void Eva3_unittest_mock::testWillComeAgain()
{
    QCOMPARE(gm->players_turn(Field::Red),true);
    gm->empty(1,2);
    QCOMPARE(gm->players_turn(Field::Red),true);
}

void Eva3_unittest_mock::testSaveGame()
{
    QCOMPARE(gm->save_game(),true);
}

void Eva3_unittest_mock::cleanupTestCase()
{
    delete gm;
    delete rm;
}

QTEST_APPLESS_MAIN(Eva3_unittest_mock)

#include "tst_eva3_unittest_mock.moc"
