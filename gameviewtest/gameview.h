#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>
#include <QLabel>
#include "resourcemanager.h"
//#include "gamemodel.h"
class GameView : public QWidget
{
    Q_OBJECT
public:
    GameView(QGridLayout* Main_layout,int N, ResourceManager* Rcm, QWidget *parent = 0);
    void forward_key(char button);
    ~GameView();
private:
    QWidget* parent;
    QGridLayout* main_layout;
    ResourceManager* rcm;
    int n;
    QVector<QLabel*> squares;
    QPushButton* new_game_button;
signals:
    void new_game();
public slots:
    void set_focus();
};

#endif // GAMEVIEW_H
