#include "start.h"

Start::Start(QWidget* Parent,QGridLayout* Main_layout)
:parent(Parent),
 main_layout(Main_layout),
 start_text(QObject::trUtf8("Játék indítása"))
{
    init_window();
}

int Start::k_num()const
{
    return k_slider->value();
}

int Start::mk_num()const
{
    return mk_slider->value();
}

void Start::init_window()
{
    //A kezdőablak felépítése
    mk_label = new QLabel(parent);
    mk_label->setText(QObject::trUtf8("Misszionárius és kannibálok száma:"));

    mk_slider = new QSlider(parent);
    mk_slider->setFixedSize(400,30);
    mk_slider->setMinimum(2);
    mk_slider->setMaximum(5);
    mk_slider->setValue(2);
    mk_slider->setOrientation(Qt::Horizontal);

    mk_lcd = new QLCDNumber(4,parent);
    mk_lcd->display(2);

    k_label = new QLabel;
    k_label->setText(QObject::trUtf8("Csónak férőhelyeinek száma:"));

    k_slider = new QSlider(parent);
    k_slider->setFixedSize(400,30);
    k_slider->setMinimum(2);
    k_slider->setMaximum(5);
    k_slider->setValue(2);
    k_slider->setOrientation(Qt::Horizontal);

    k_lcd = new QLCDNumber(4);
    k_lcd->display(2);

    start_button = new QPushButton(start_text,parent);

    main_layout->addWidget(mk_label,0,0);
    main_layout->addWidget(mk_slider,1,0);
    main_layout->addWidget(mk_lcd,1,1);
    main_layout->addWidget(k_label,2,0);
    main_layout->addWidget(k_slider,3,0);
    main_layout->addWidget(k_lcd,3,1);
    main_layout->addWidget(start_button,4,0,1,2);

    QObject::connect(mk_slider,SIGNAL(valueChanged(int)),mk_lcd,SLOT(display(int)));
    QObject::connect(k_slider,SIGNAL(valueChanged(int)),k_lcd,SLOT(display(int)));
    QObject::connect(start_button,SIGNAL(clicked()),parent,SLOT(startgame()));
}

Start::~Start()
{   
    QLayoutItem *child;
    while ((child = main_layout->takeAt(0)) != 0)
    {
        delete child->widget();
    }
}
