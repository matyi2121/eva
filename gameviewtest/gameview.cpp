#include "gameview.h"
#include <QMessageBox>

GameView::GameView(QGridLayout *Main_layout,int N, ResourceManager* Rcm, QWidget *Parent)
    : QWidget(Parent),
      parent(Parent),
      main_layout(Main_layout),
      rcm(Rcm),
      n(N)
{
    QLabel* l;
    squares.resize(n*n);
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            l = new QLabel();
            l->setPixmap(rcm->get_picture("bg")->scaled(QSize(20,20)));
            l->setScaledContents(true);
            main_layout->addWidget(l,i,j);
            squares.push_back(l);
        }
    }

    //gm = new GameModel("p1","p2",n,n);

    new_game_button = new QPushButton(QObject::trUtf8("Új játék"));
    main_layout->addWidget(new_game_button,n,0,1,n);

    //QObject::connect(gm,SIGNAL(set_focus()),this,SLOT(set_focus()));
    //QObject::connect(gm,SIGNAL(init_players(QString,Coord,Coord,QString,Coord,Coord)),this,SLOT(init_players(QString,Coord,Coord,QString,Coord,Coord)));
    QObject::connect(new_game_button,SIGNAL(clicked()),parent,SLOT(new_game()));
    QObject::connect(this,SIGNAL(new_game()),parent,SLOT(new_game()));
    //QObject::connect(gm,SIGNAL(collision(GameModel::Collision)),this,SLOT(game_over(GameModel::Collision)));
    //QObject::connect(gm,SIGNAL(step(Coord,Coord,QString)),this,SLOT(refresh(Coord,Coord,QString)));
}

void GameView::forward_key(char button)
{
    //gm->change_dir(button);
}

void GameView::set_focus()
{
    this->setFocus();
}

GameView::~GameView()
{
    foreach (QLabel* label, squares)
    {
        main_layout->removeWidget(label);
        delete label;
    }
    main_layout->removeWidget(new_game_button);
    delete new_game_button;
    //delete gm;
}
