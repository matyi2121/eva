#include "startview.h"
#include <QLayoutItem>
StartView::StartView(QGridLayout* Main_layout, QWidget *Parent)
    : QWidget(Parent),
      parent(Parent),
      main_layout(Main_layout),
      smallest_n(4)
{
    size_cb = new QComboBox();
    for(int i = 1; i < 4; ++i)
    {
        int currn = i * smallest_n;
        QString val = QString(QObject::trUtf8("%1")).arg(currn);
        size_cb->addItem(val);
    }
    main_layout->addWidget(size_cb,0,0);

    start_button = new QPushButton(QObject::trUtf8("Új játék kezdése"));
    main_layout->addWidget(start_button,1,0);

    QObject::connect(size_cb,SIGNAL(currentIndexChanged(int)),parent,SLOT(change_n(int)));
    QObject::connect(start_button,SIGNAL(clicked()),parent,SLOT(start_game()));
}

StartView::~StartView()
{
    QLayoutItem* child;
    while((child = main_layout->takeAt(0)) != 0)
    {
        delete child->widget();
    }
}
