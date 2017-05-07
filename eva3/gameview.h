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
    ResourceManager* rm;
    int n;
    QPushButton* new_game;
    QPushButton* load_game;
    QPushButton* save_game;
    GameModel* gm;
    void create_board();
    void delete_board();
signals:
    void game_over();
public slots:
    void load_game_caller();
    void save_game_caller();
    void empty_bowl();
    void refresh();
    void show_winner(int);
    void size_changed(int);
};

#endif // GAMEVIEW_H
