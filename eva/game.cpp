#include "game.h"

Game::Game(QWidget* Parent,int Mknum,int Knum,QGridLayout* Main_layout, ResourceManager* Rcm)
    :QWidget(Parent),
     parent(Parent),
     cann('c'),
     miss('m'),
     main_layout(Main_layout),
     rcm(Rcm)
{
    gm = new GameManager(Mknum,Knum);
    init_window();
}

void Game::init_window()
{
    //A játékablak felépítése

    left_col();
    mid_col();
    right_col();

    QObject::connect(this,SIGNAL(victory()),parent,SLOT(newgame()));
}

void Game::left_col()
{
    boatc_lb = new QLabel("Hány kannibál menjen a csónakba?",this);
    boatc_lb->setWordWrap(true);
    main_layout->addWidget(boatc_lb,0,0);

    boatc_slider = new QSlider(Qt::Horizontal,this);
    boatc_slider->setMinimum(0);
    boatc_slider->setMaximum(5);
    boatc_slider->setValue(0);
    main_layout->addWidget(boatc_slider,1,0);

    boatc_lcd = new QLCDNumber(1,this);
    boatc_lcd->display(0);
    main_layout->addWidget(boatc_lcd,2,0);

    boatm_lb = new QLabel("Hány misszionárius menjen a csónakba?",this);
    boatm_lb->setWordWrap(true);
    main_layout->addWidget(boatm_lb,3,0);

    boatm_slider = new QSlider(Qt::Horizontal,this);
    boatm_slider->setMinimum(0);
    boatm_slider->setMaximum(5);
    boatm_slider->setValue(0);
    main_layout->addWidget(boatm_slider,4,0);

    boatm_lcd = new QLCDNumber(1,this);
    boatm_lcd->display(0);
    main_layout->addWidget(boatm_lcd,5,0);

    left_part = new QLabel("bal part",this);
    main_layout->addWidget(left_part,6,0);

    mleft_pic = new QLabel(this);
    mleft_pic->setPixmap(rcm->get_pics(QString("mfold%1").arg(gm->get_left_num(miss)))->scaled(200,150));
    main_layout->addWidget(mleft_pic,7,0);

    cleft_pic = new QLabel(this);
    cleft_pic->setPixmap(rcm->get_pics(QString("kfold%1").arg(gm->get_left_num(cann)))->scaled(200,150));
    main_layout->addWidget(cleft_pic,8,0);

    QObject::connect(boatc_slider,SIGNAL(valueChanged(int)),boatc_lcd,SLOT(display(int)));
    QObject::connect(boatm_slider,SIGNAL(valueChanged(int)),boatm_lcd,SLOT(display(int)));
}

void Game::mid_col()
{
    get_offc_lb = new QLabel(QObject::trUtf8("Hány kannibál szálljon le a másik partra érkezéskor?"),this);
    get_offc_lb->setWordWrap(true);
    main_layout->addWidget(get_offc_lb,0,2);

    get_offc_slider = new QSlider(Qt::Horizontal,this);
    get_offc_slider->setMinimum(0);
    get_offc_slider->setMaximum(5);
    get_offc_slider->setValue(0);
    main_layout->addWidget(get_offc_slider,1,2);

    get_offc_lcd = new QLCDNumber(1,this);
    get_offc_lcd->display(0);
    main_layout->addWidget(get_offc_lcd,2,2);

    get_offm_lb = new QLabel(QObject::trUtf8("Hány misszionárius szálljon le a másik partra érkezéskor?"),this);
    get_offm_lb->setWordWrap(true);
    main_layout->addWidget(get_offm_lb,3,2);

    get_offm_slider = new QSlider(Qt::Horizontal,this);
    get_offm_slider->setMinimum(0);
    get_offm_slider->setMaximum(5);
    get_offm_slider->setValue(0);
    main_layout->addWidget(get_offm_slider,4,2);

    get_offm_lcd = new QLCDNumber(1,this);
    get_offm_lcd->display(0);
    get_offm_lcd->setFixedHeight(30);
    main_layout->addWidget(get_offm_lcd,5,2);

    leftright_lb = new QLabel(QString(QObject::trUtf8("Jelenleg %1 megy a csónak")).arg(gm->get_dir()),this);
    leftright_lb->setWordWrap(true);
    main_layout->addWidget(leftright_lb,6,1,1,2);

    boatm_pic = new QLabel(this);
    boatm_pic->setPixmap(rcm->get_pics(QString("mcsonak%1").arg(gm->get_boat_num(miss)))->scaled(QSize(200,150)));
    main_layout->addWidget(boatm_pic,8,1);

    boatc_pic = new QLabel(this);
    boatc_pic->setPixmap(rcm->get_pics(QString("kcsonak%1").arg(gm->get_boat_num(cann)))->scaled(QSize(200,150)));
    main_layout->addWidget(boatc_pic,8,2);

    QObject::connect(get_offc_slider,SIGNAL(valueChanged(int)),get_offc_lcd,SLOT(display(int)));
    QObject::connect(get_offm_slider,SIGNAL(valueChanged(int)),get_offm_lcd,SLOT(display(int)));
}

void Game::right_col()
{
    new_game = new QPushButton(QObject::trUtf8("Új játék"),this);
    main_layout->addWidget(new_game,0,3);

    into_boat = new QPushButton(QObject::trUtf8("Csónakba rak"),this);
    main_layout->addWidget(into_boat,1,3);

    put_back = new QPushButton(QObject::trUtf8("Partra rak"),this);
    main_layout->addWidget(put_back,2,3);

    ferry = new QPushButton(QObject::trUtf8("Átkel"),this);
    main_layout->addWidget(ferry,3,3);

    right_part = new QLabel("jobb part",this);
    main_layout->addWidget(right_part,6,3);

    mright_pic = new QLabel(this);
    mright_pic->setPixmap(rcm->get_pics(QString("mfold%1").arg(gm->get_right_num(miss)))->scaled(200,150));
    main_layout->addWidget(mright_pic,7,3);

    kright_pic = new QLabel(this);
    kright_pic->setPixmap(rcm->get_pics(QString("kfold%1").arg(gm->get_right_num(cann)))->scaled(200,150));
    main_layout->addWidget(kright_pic,8,3);

    QObject::connect(new_game,SIGNAL(clicked()),parent,SLOT(newgame()));
    QObject::connect(ferry,SIGNAL(clicked()),this,SLOT(ferry_clicked()));
    QObject::connect(put_back,SIGNAL(clicked()),this,SLOT(put_back_clicked()));
    QObject::connect(into_boat,SIGNAL(clicked()),this,SLOT(into_boat_clicked()));
}

void Game::refresh_layout()
{
    boatc_pic->setPixmap(rcm->get_pics(QString("kcsonak%1").arg(gm->get_boat_num(cann)))->scaled(QSize(200,150)));
    boatm_pic->setPixmap(rcm->get_pics(QString("mcsonak%1").arg(gm->get_boat_num(miss)))->scaled(QSize(200,150)));
    mleft_pic->setPixmap(rcm->get_pics(QString("mfold%1").arg(gm->get_left_num(miss)))->scaled(QSize(200,150)));
    cleft_pic->setPixmap(rcm->get_pics(QString("kfold%1").arg(gm->get_left_num(cann)))->scaled(QSize(200,150)));
    mright_pic->setPixmap(rcm->get_pics(QString("mfold%1").arg(gm->get_right_num(miss)))->scaled(QSize(200,150)));
    kright_pic->setPixmap(rcm->get_pics(QString("kfold%1").arg(gm->get_right_num(cann)))->scaled(QSize(200,150)));

    leftright_lb->setText(QString(QObject::trUtf8("Jelenleg %1 megy a csónak")).arg(gm->get_dir()));
}

/*
 * Abban az esetben, ha vannak a csónakban, átjuttatja őket a másik oldalra,
 * hogy ha nem halnak meg közben a misszionáriusok valamelyik oldalon.
*/
void Game::ferry_clicked()
{
    int cval = get_offc_slider->value();
    int mval = get_offm_slider->value();
    QMessageBox qmsg;
    if(!gm->is_boat_empty())
    {
        if(gm->are_enough_on_boat(cval,mval))
        {
            if(!gm->check_lose_cond())
            {
                if(gm->to_right())
                {
                    gm->arrival(gm->toright,cval,mval);
                }
                else
                {
                    gm->arrival(gm->toleft,cval,mval);
                }
                refresh_layout();
            }
            else
            {
                qmsg.setText(QObject::trUtf8("Az adott lépés a valamelyik oldalon a misszionáriusok halálát okozná!"));
                qmsg.exec();
            }
            if(gm->is_finished())
            {
                qmsg.setText((QString(QObject::trUtf8("Gratulálok %1 átkeléssel oldottad meg!")).arg(gm->get_steps())));
                qmsg.exec();
                emit victory();
            }
        }
        else
        {
            qmsg.setText(QObject::trUtf8("Nincs annyi ember a csónakban"));
            qmsg.exec();
        }
    }
    else
    {
        qmsg.setText(QObject::trUtf8("Nincs senki a csónakban"));
        qmsg.exec();
    }
}
//Megnézi, hogy vannak-e a csónakban, és ha igen akkor visszateszi a megfelelő oldalra őket.
void Game::put_back_clicked()
{
    if(!gm->is_boat_empty())
    {
        gm->empty_ship();
        refresh_layout();
    }
    else
    {
        QMessageBox qmsg;
        qmsg.setText(QObject::trUtf8("Nincs senki a csónakban"));
        qmsg.exec();
    }
}

void Game::into_boat_clicked()
{
    int cval = boatc_slider->value();
    int mval = boatm_slider->value();
    QMessageBox qmsg;

    if(gm->to_right())//1.
    {
        if(gm->has_place(cval,mval))//3.
        {
            if(gm->are_enough_on_side(gm->toleft,cval,mval))//2-1.
            {
                gm->fill_ship(cval,mval);
            }
            else
            {
                qmsg.setText(QObject::trUtf8("Nincs elég az adott oldalon!"));
                qmsg.exec();
            }
        }
        else
        {
            qmsg.setText(QObject::trUtf8("Nincs elég hely"));
            qmsg.exec();
        }
    }
    else
    {
        if(gm->has_place(cval,mval))
        {
            if(gm->are_enough_on_side(gm->toright,cval,mval))//2-2.
            {
                gm->fill_ship(cval,mval);
            }
            else
            {
                qmsg.setText(QObject::trUtf8("Nincs elég az adott oldalon!"));
                qmsg.exec();
            }
        }
        else
        {
            qmsg.setText(QObject::trUtf8("Nincs elég hely"));
            qmsg.exec();
        }
    }
    refresh_layout();
}
Game::~Game()
{
    QLayoutItem *child;
    while ((child = main_layout->takeAt(0)) != 0)
    {
        delete child->widget();
    }
    delete gm;
}
