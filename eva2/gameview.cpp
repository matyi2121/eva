#include "gameview.h"

GameView::GameView(QGridLayout *Main_layout,int N, ResourceManager* Rcm, QWidget *Parent)
    : QWidget(Parent),
      parent(Parent),
      main_layout(Main_layout),
      rcm(Rcm),
      n(N)
{
    gm = new GameModel("p1","p2",n,n);
    QLabel* l;
    squares.resize(n*n);
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            l = new QLabel();
            l->setPixmap(rcm->get_picture("bg")->scaled(QSize(20,20)));
            main_layout->addWidget(l,i,j);
            squares.push_back(l);
        }
    }
    new_game_button = new QPushButton(QObject::trUtf8("Új játék"));
    main_layout->addWidget(new_game_button,n,0,1,n);
    QObject::connect(new_game_button,SIGNAL(clicked()),parent,SLOT(new_game()));
}

void GameView::game_over(GameModel::Collision c)
{
    if(c == GameModel::Collision::Player1)//p1 collided with something
    {

    }
    else if(c == GameModel::Collision::Player2)
    {

    }
    else//both of them collided at the same time
    {

    }
    emit new_game();
}

void GameView::refresh(Coord prev_pos, Coord curr_pos, QString player_id)
{
    Coord dir = curr_pos - prev_pos;
    QLabel* tmp = dynamic_cast<QLabel*>(main_layout->itemAtPosition(prev_pos.y,prev_pos.x)->widget());
    int orientation = dir.x == 0 ? 0 : 1;
    tmp->setPixmap(rcm->get_picture( QString("%1%2").arg(player_id).arg(orientation))->scaled(QSize(20,20)));

    tmp = dynamic_cast<QLabel*>(main_layout->itemAtPosition(curr_pos.y,curr_pos.x)->widget());
    tmp->setPixmap(rcm->get_picture( QString("%1%2%3").arg(player_id).arg(dir.x).arg(dir.y))->scaled(QSize(20,20)));
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
    delete gm;
}
