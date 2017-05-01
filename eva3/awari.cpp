#include "awari.h"

awari::awari(QWidget *parent) :
    QWidget(parent),
    game_view(NULL),
    n(4)
{
    main_layout = new QGridLayout;
    setLayout(main_layout);
    start_view = new StartView(main_layout,this);
}

awari::~awari()
{
    if(start_view != NULL)
        delete start_view;
    if(game_view != NULL)
        delete game_view;
    delete main_layout;
}

void awari::start_game()
{
    delete start_view;
    start_view = NULL;
    game_view = new GameView(main_layout,n,this);
}

void awari::new_game()
{
    delete game_view;
    game_view = NULL;
    start_view = new StartView(main_layout,this);
    n = 4;
}

void awari::change_n(int N)
{
    n = 4*(N+1);
}
