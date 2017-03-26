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
            main_layout->addWidget(l,i,j);
            squares.push_back(l);
        }
    }

    gm = new GameModel("p1","p2",n,n);

    new_game_button = new QPushButton(QObject::trUtf8("Új játék"));
    main_layout->addWidget(new_game_button,n,0,1,n);
    QObject::connect(gm,SIGNAL(init_players(QString,Coord,Coord,QString,Coord,Coord)),this,SLOT(init_players(QString,Coord,Coord,QString,Coord,Coord)));
    QObject::connect(new_game_button,SIGNAL(clicked()),parent,SLOT(new_game()));
    QObject::connect(this,SIGNAL(new_game()),parent,SLOT(new_game()));
    QObject::connect(gm,SIGNAL(collision(GameModel::Collision)),this,SLOT(game_over(GameModel::Collision)));
    QObject::connect(gm,SIGNAL(step(Coord,Coord,QString)),this,SLOT(refresh(Coord,Coord,QString)));
}

void GameView::game_over(GameModel::Collision c)
{
    QMessageBox qmsg;
    if(c == GameModel::Collision::Player1)//p1 collided with something
    {
        qmsg.setText(QObject::trUtf8("Player 2 won!"));
        qmsg.exec();
    }
    else if(c == GameModel::Collision::Player2)
    {
        qmsg.setText(QObject::trUtf8("Player 1 won!"));
        qmsg.exec();
    }
    else//both of them collided at the same time
    {
        qmsg.setText(QObject::trUtf8("Draw!"));
        qmsg.exec();
    }
    emit new_game();
}

void GameView::refresh(Coord prev_pos, Coord curr_pos, QString player_id)
{
    try
    {
        Coord dir = curr_pos - prev_pos;
        QLabel* tmp = dynamic_cast<QLabel*>(main_layout->itemAtPosition(prev_pos.y,prev_pos.x)->widget());
        int orientation = dir.x == 0 ? 0 : 1;
        tmp->setPixmap(rcm->get_picture( QString("%1%2").arg(player_id).arg(orientation))->scaled(QSize(20,20)));

        tmp = dynamic_cast<QLabel*>(main_layout->itemAtPosition(curr_pos.y,curr_pos.x)->widget());
        tmp->setPixmap(rcm->get_picture( QString("%1%2%3").arg(player_id).arg(dir.x).arg(dir.y))->scaled(QSize(20,20)));
    }
    catch(ResourceManager::Exceptions e)
    {
        QMessageBox qmsg;
        qmsg.setText("refresh");
        qmsg.exec();
    }
}
void GameView::init_players(QString p1_id,Coord p1_pos,Coord p1_dir,QString p2_id,Coord p2_pos,Coord p2_dir)
{
    QLabel* tmp = dynamic_cast<QLabel*>(main_layout->itemAtPosition(p1_pos.y,p1_pos.x)->widget());
    tmp->setPixmap(rcm->get_picture( QString("%1%2%3").arg(p1_id).arg(p1_dir.x).arg(p1_dir.y))->scaled(QSize(20,20)));

    tmp = dynamic_cast<QLabel*>(main_layout->itemAtPosition(p2_pos.y,p2_pos.x)->widget());
    tmp->setPixmap(rcm->get_picture( QString("%1%2%3").arg(p2_id).arg(p2_dir.x).arg(p2_dir.y))->scaled(QSize(20,20)));
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
