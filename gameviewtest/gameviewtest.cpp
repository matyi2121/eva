#include <QString>
#include <QtTest>
#include "tron.h"
class GameviewtestTest : public QObject
{
    Q_OBJECT

public:
    GameviewtestTest();
    Tron* w;
private Q_SLOTS:
    void initTestCase()
    {
        w = new Tron();
    }

    void change_n();

    void start_game()
    {
        w->start_game();
    }
    void new_game()
    {
        w->new_game();
    }

    void cleanupTestCase()
    {
        delete w;
    }
};
GameviewtestTest::GameviewtestTest()
{
}

void GameviewtestTest::change_n()
{
    w->change_n(2);
    QCOMPARE(w->n,2);
    w->change_n(0);
    QCOMPARE(w->n,0);
}

QTEST_MAIN(GameviewtestTest)

#include "gameviewtest.moc"
