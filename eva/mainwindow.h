#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "resourcemanager.h"
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

class Start;
class Game;
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void startgame();
    void newgame();
private:
    void window_init();
    Start* start;
    Game* game;
    ResourceManager* rcm;
    QGridLayout* main_layout;
};

#endif // MAINWINDOW_H
