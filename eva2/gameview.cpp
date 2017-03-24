#include "gameview.h"

GameView::GameView(QGridLayout *Main_layout,int N, ResourceManager* Rcm, QWidget *Parent)
    : QWidget(Parent),
      parent(Parent),
      main_layout(Main_layout),
      rcm(Rcm),
      n(N)
{
    QLabel* l;
    main_layout->setSizeConstraint(QLayout::SetNoConstraint);

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
    main_layout->setSizeConstraint(QLayout::SetFixedSize);
    QObject::connect(new_game_button,SIGNAL(clicked()),parent,SLOT(new_game()));
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
}
