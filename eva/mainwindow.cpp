#include "mainwindow.h"
#include "start.h"
#include "game.h"
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    start(0),
    game(0)
{
    rcm = new ResourceManager;
    window_init();
}

void MainWindow::window_init()
{
    setWindowTitle(trUtf8("Első Beadandó"));
    setFixedSize(800,640);
    main_layout = new QGridLayout(this);
    main_layout->setHorizontalSpacing(0);
    main_layout->setVerticalSpacing(0);
    setLayout(main_layout);
    start = new Start(this,main_layout);
}

void MainWindow::startgame()
{
    int mknum = start->mk_num();
    int knum = start->k_num();
    delete start;
    start = 0;
    game = new Game(this,mknum,knum,main_layout,rcm);
}
void MainWindow::newgame()
{
    if(game != 0)
    {
        delete game;
        game = 0;
    }
    start = new Start(this,main_layout);
}

MainWindow::~MainWindow()
{
    if(start != 0)
        delete start;
    if(game != 0)
        delete game;
    delete rcm;
}
