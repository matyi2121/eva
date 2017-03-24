#include "tron.h"
Tron::Tron(QWidget *parent)
    : QWidget(parent),
      game_view(0),
      n(0)
{
    rcm = new ResourceManager;
    main_layout = new QGridLayout;
    main_layout->setHorizontalSpacing(0);
    main_layout->setVerticalSpacing(0);
    main_layout->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(main_layout);
    start_view = new StartView(main_layout,this);

}

void Tron::new_game()
{
    delete game_view;
    game_view = nullptr;
    start_view = new StartView(main_layout,this);
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
