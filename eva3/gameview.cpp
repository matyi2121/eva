#include "gameview.h"
#include <QLayoutItem>
#include <QMessageBox>
GameView::GameView(QGridLayout* Main_layout,int N, QWidget *Parent)
    : QWidget(Parent),
      parent(Parent),
      main_layout(Main_layout),
      n(N)
{
    ResourceManager* rm = new ResourceManager;
    gm = new GameModel(rm,n,this);
    create_board();
}
void GameView::show_winner(int w)
{
    QMessageBox qmsg;
    if(w == 1)
    {
        qmsg.setText(QObject::trUtf8("A kék játékos nyert"));
    }
    else if(w == 2)
    {
        qmsg.setText(QObject::trUtf8("A piros játékos nyert"));
    }
    else
    {
        qmsg.setText(QObject::trUtf8("Döntetlen"));
    }
    qmsg.exec();
    emit game_over();
}

void GameView::create_board()
{
    QPushButton* tmp = new QPushButton("0");
    tmp->setStyleSheet("background-color: blue");
    main_layout->addWidget(tmp,0,0,2,1);

    for(int i = 1; i <= n; ++i)
    {
        tmp = new QPushButton("6");
        tmp->setStyleSheet("background-color: blue");
        main_layout->addWidget(tmp,0,i);
        QObject::connect(tmp,SIGNAL(clicked()),this,SLOT(empty_bowl()));
    }
    tmp = new QPushButton("0");
    tmp->setStyleSheet("background-color: red");
    main_layout->addWidget(tmp,0,n+1,2,1);
    for(int i = 1; i <= n; ++i)
    {
        tmp = new QPushButton("6");
        tmp->setStyleSheet("background-color: red");
        main_layout->addWidget(tmp,1,i);
        QObject::connect(tmp,SIGNAL(clicked()),this,SLOT(empty_bowl()));
    }
    new_game = new QPushButton(QObject::trUtf8("Új játék"));
    main_layout->addWidget(new_game,2,0);

    load_game = new QPushButton(QObject::trUtf8("Játék betöltése"));
    main_layout->addWidget(load_game,2,n);

    save_game = new QPushButton(QObject::trUtf8("Játék mentése"));
    main_layout->addWidget(save_game,2,n+1);

    QObject::connect(new_game,SIGNAL(clicked()),parent,SLOT(new_game()));
    QObject::connect(load_game,SIGNAL(clicked()),this,SLOT(load_game_caller()));
    QObject::connect(save_game,SIGNAL(clicked()),this,SLOT(save_game_caller()));

    QObject::connect(gm,SIGNAL(refresh_window()),this,SLOT(refresh()));

    QObject::connect(gm,SIGNAL(winner(int)),this,SLOT(show_winner(int)));
    QObject::connect(this,SIGNAL(game_over()),parent,SLOT(new_game()));
    QObject::connect(gm,SIGNAL(size_changed(int)),this,SLOT(size_changed(int)));
}

void GameView::delete_board()
{
    QLayoutItem* child;
    while((child = main_layout->takeAt(0)) != 0)
    {
        delete child->widget();
    }
}

void GameView::load_game_caller()
{
    if(!gm->load_game())
    {//küldjön signalt a model a view-nak ha szükség van átméretezésre
        QMessageBox::warning(this,QObject::trUtf8("Hiba"),QObject::trUtf8("A játék betöltése sikertelen"));
    }
}

void GameView::save_game_caller()
{
    if(!gm->save_game())
    {
        QMessageBox::warning(this,QObject::trUtf8("Hiba"),QObject::trUtf8("A játék mentése sikertelen"));
    }
}

void GameView::empty_bowl()
{
    QPushButton* sender_button = dynamic_cast<QPushButton*>(sender());
    //sender button megkeresese main_layoutban
    int ind = main_layout->indexOf(sender_button);
    int row = 0;
    int col = 0;
    int rowspan = 0;
    int colspan = 0;
    main_layout->getItemPosition(ind,&row,&col,&rowspan,&colspan);
    QMessageBox qmsg;
    qmsg.setText("Nem te vagy a soron!");

    Field f = row == 0 ? Field::Blue : Field::Red;
    if(gm->players_turn(f))
    {
        if(!gm->is_empty(row,col))
        {
            gm->empty(row,col);
        }
        else
        {
            qmsg.setText(QObject::trUtf8("Üres a tál!"));
            qmsg.exec();
        }
    }
    else
    {
        qmsg.exec();
    }
}

void GameView::refresh()
{
    //set blue collector
    QPushButton* tmp = qobject_cast<QPushButton*>(main_layout->itemAtPosition(0,0)->widget());
    tmp->setText(QString::number(gm->get_collector(Field::Blue)));
    //set red collector
    tmp = qobject_cast<QPushButton*>(main_layout->itemAtPosition(0,n+1)->widget());
    tmp->setText(QString::number(gm->get_collector(Field::Red)));
    //set remaining fields
    for(int i = 1; i <= n; ++i)
    {
        tmp = qobject_cast<QPushButton*>(main_layout->itemAtPosition(0,i)->widget());
        tmp->setText(QString::number(gm->get_field(Field::Blue,i)));
        tmp = qobject_cast<QPushButton*>(main_layout->itemAtPosition(1,i)->widget());
        tmp->setText(QString::number(gm->get_field(Field::Red,i)));
    }
}

void GameView::size_changed(int N)
{
    //delete all
    delete_board();
    n = N;
    create_board();
    //create new board
}

GameView::~GameView()
{
    delete_board();
    delete gm;
}
