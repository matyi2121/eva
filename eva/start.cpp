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
    mk_slider->setMinimum(2);
    mk_slider->setMaximum(5);
    mk_slider->setValue(2);
    mk_slider->setOrientation(Qt::Horizontal);

    mk_lcd = new QLCDNumber(4,parent);
    mk_lcd->display(2);

    //mk_sor = new QHBoxLayout;
    //mk_sor->addWidget(mk_slider);
    //mk_sor->addWidget(mk_lcd);

    k_label = new QLabel;
    k_label->setText(QObject::trUtf8("Csónak férőhelyeinek száma:"));

    k_slider = new QSlider(parent);
    k_slider->setMinimum(2);
    k_slider->setMaximum(5);
    k_slider->setValue(2);
    k_slider->setOrientation(Qt::Horizontal);

    k_lcd = new QLCDNumber(4,parent);
    k_lcd->display(2);

    //k_sor = new QHBoxLayout;
    //k_sor->addWidget(k_slider);
    //k_sor->addWidget(k_lcd);

    start_button = new QPushButton(start_text,parent);

    start_layout = new QGridLayout;
    start_layout->addWidget(mk_label,0,0);
    start_layout->addWidget(mk_slider,1,0);
    start_layout->addWidget(mk_lcd,1,1);
    start_layout->addWidget(k_label,2,0);
    start_layout->addWidget(k_slider,3,0);
    start_layout->addWidget(k_lcd,3,1);
    start_layout->addWidget(start_button,4,0);
    main_layout->addLayout(start_layout,0,0);

    QObject::connect(mk_slider,SIGNAL(valueChanged(int)),mk_lcd,SLOT(display(int)));
    QObject::connect(k_slider,SIGNAL(valueChanged(int)),k_lcd,SLOT(display(int)));
    QObject::connect(start_button,SIGNAL(clicked()),parent,SLOT(startgame()));
}

Start::~Start()
{   
    QLayoutItem *child;
    while ((child = start_layout->takeAt(0)) != 0)
    {
        delete child->widget();
    }

    main_layout->removeItem(start_layout);
    delete start_layout;
}
