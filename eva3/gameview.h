#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include "gamemodel.h"
class GameView : public QWidget
{
    Q_OBJECT
public:
    explicit GameView(QGridLayout* Main_layout,int N, QWidget *parent = 0);
    ~GameView();
private:
    QWidget* parent;
    QGridLayout* main_layout;
    int n;
    QPushButton* new_game;
    QPushButton* load_game;
    QPushButton* save_game;
    GameModel* gm;
signals:
    void game_over();
public slots:
    void save_game_caller();
    void empty_bowl();
    void refresh();
    void show_winner(int);
};

#endif // GAMEVIEW_H
