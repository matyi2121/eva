#include "tron.h"
#include <QMouseEvent>
#include <QApplication>
#include <QMessageBox>

Tron::Tron(QWidget *parent)
    : QWidget(parent),
      game_view(0),
      n(0)
{
    rcm = new ResourceManager;
    main_layout = new QGridLayout;
    main_layout->setHorizontalSpacing(0);
    main_layout->setVerticalSpacing(0);

    this->setFocusPolicy(Qt::StrongFocus);
    setLayout(main_layout);
    start_view = new StartView(main_layout,this);

}

void Tron::new_game()
{
    delete game_view;
    game_view = nullptr;
    start_view = new StartView(main_layout,this);
    QWidget::adjustSize();
    n = 0;
}

void Tron::start_game()
{
    delete start_view;
    start_view = nullptr;
    game_view = new GameView(main_layout,(n+1)*12,rcm,this);
}

void Tron::change_n(int N)
{
    n = N;
}

void Tron::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_P)
    {
        game_view->forward_key('p');
    }
    else if(event->key() == Qt::Key_W)
    {
        game_view->forward_key('w');
    }
    else if(event->key() == Qt::Key_A)
    {
        game_view->forward_key('a');
    }
    else if(event->key() == Qt::Key_S)
    {
        game_view->forward_key('s');
    }
    else if(event->key() == Qt::Key_D)
    {
        game_view->forward_key('d');
    }
    else if(event->key() == Qt::Key_Up)
    {
        game_view->forward_key('U');
    }
    else if(event->key() == Qt::Key_Left)
    {
        game_view->forward_key('L');
    }
    else if(event->key() == Qt::Key_Down)
    {
        game_view->forward_key('D');
    }
    else if(event->key() == Qt::Key_Right)
    {
        game_view->forward_key('R');
    }
}

Tron::~Tron()
{
    if(start_view != nullptr)
    {
        delete start_view;
    }
    if(game_view != nullptr)
    {
        delete game_view;
    }
    delete rcm;
}
