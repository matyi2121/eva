#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>
#include <QLabel>
#include "resourcemanager.h"
class GameView : public QWidget
{
    Q_OBJECT
public:
    GameView(QGridLayout* Main_layout,int N, ResourceManager* Rcm, QWidget *parent = 0);
    ~GameView();
private:
    QWidget* parent;
    QGridLayout* main_layout;
    ResourceManager* rcm;
    int n;
    QVector<QLabel*> squares;
    QPushButton* new_game_button;
signals:

public slots:
};

#endif // GAMEVIEW_H
