#ifndef TRON_H
#define TRON_H

#include <QWidget>
#include <QGridLayout>
#include "startview.h"
#include "gameview.h"
#include "resourcemanager.h"
class Tron : public QWidget
{
    Q_OBJECT

public:
    Tron(QWidget *parent = 0);
    ~Tron();
private:
    ResourceManager* rcm;
    StartView* start_view;
    GameView* game_view;
    QGridLayout* main_layout;
    int n;
    void keyPressEvent(QKeyEvent *event);
public slots:
    void new_game();
    void change_n(int N);
    void start_game();
};

#endif // TRON_H
