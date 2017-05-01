#ifndef AWARI_H
#define AWARI_H

#include <QWidget>
#include <QGridLayout>
#include "startview.h"
#include "gameview.h"
class awari : public QWidget
{
    Q_OBJECT

public:
    explicit awari(QWidget *parent = 0);
    ~awari();

private:
    QGridLayout* main_layout;
    StartView* start_view;
    GameView* game_view;
    int n;
public slots:
    void start_game();
    void new_game();
    void change_n(int N);
};

#endif // AWARI_H
