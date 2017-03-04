#include "game.h"

Game::Game(QWidget* parent)
    :QWidget(parent)
{

}

Game::Game(QWidget* Parent,int Mknum,int Knum,QGridLayout* Main_layout, ResourceManager* Rcm)
    :QWidget(Parent),
     parent(Parent),
     main_layout(Main_layout),
     mknum(Mknum),
     knum(Knum),
     rcm(Rcm),
     cb_text1(QObject::trUtf8("balról jobbra")),
     cb_text2(QObject::trUtf8("jobbról balra")),
     csonakba_text(QObject::trUtf8("Csónakba rak")),
     visszarak_text(QObject::trUtf8("Visszarak")),
     atkel_text(QObject::trUtf8("Átkel")),
     new_game_text(QObject::trUtf8("Új játék")),
     lepes_szam(0),
     irany(""),
     bal_szam(Mknum),
     csonak_szam(0),
     jobb_szam(0)
{
    init_window();
}

void Game::init_window()
{
    //A játékablak felépítése
    game_layout = new QGridLayout;
    game_layout->setHorizontalSpacing(0);
    game_layout->setVerticalSpacing(0);
    new_game = new QPushButton(new_game_text,this);

    //Bal oszlop
    baljobb_cb = new QComboBox(this);
    baljobb_cb->addItem(cb_text1);
    baljobb_cb->addItem(cb_text2);
    game_layout->addWidget(baljobb_cb,0,0);

    csonak_lb = new QLabel("Hány kannibál-misszionárius menjen a csónakba?");
    game_layout->addWidget(csonak_lb,1,0);

    csonak_slider = new QSlider(Qt::Horizontal,this);
    csonak_slider->setMinimum(1);
    csonak_slider->setMaximum(5);
    csonak_slider->setValue(1);
    game_layout->addWidget(csonak_slider,2,0);

    csonak_lcd = new QLCDNumber(1,this);
    csonak_lcd->display(1);
    game_layout->addWidget(csonak_lcd,3,0);

    mkbal_pic = new QLabel(this);
    mkbal_pic->setPixmap(rcm->get_fold(QString("fold%1").arg(bal_szam))->scaled(200,150));
    game_layout->addWidget(mkbal_pic,4,0);

    //kozep
    folyo_pic = new QLabel(this);
    folyo_pic->setPixmap(rcm->get_viz()->scaled(QSize(200,400)));
    game_layout->addWidget(folyo_pic,0,1,4,1);

    csonak_pic = new QLabel(this);
    csonak_pic->setPixmap(rcm->get_csonak(QString("csonak%1").arg(csonak_szam))->scaled(QSize(200,150)));
    game_layout->addWidget(csonak_pic,4,1);
    //jobb
    game_layout->addWidget(new_game,0,2);

    csonakba = new QPushButton(csonakba_text);
    game_layout->addWidget(csonakba,1,2);

    visszarak = new QPushButton(visszarak_text);
    game_layout->addWidget(visszarak,2,2);

    atkel = new QPushButton(atkel_text);
    game_layout->addWidget(atkel,3,2);

    mkjobb_pic = new QLabel(this);
    mkjobb_pic->setPixmap(rcm->get_fold(QString("fold%1").arg(jobb_szam))->scaled(200,150));
    game_layout->addWidget(mkjobb_pic,4,2);

    main_layout->addLayout(game_layout,0,0);

    QObject::connect(new_game,SIGNAL(clicked()),parent,SLOT(newgame()));
    QObject::connect(csonak_slider,SIGNAL(valueChanged(int)),csonak_lcd,SLOT(display(int)));
    QObject::connect(atkel,SIGNAL(clicked()),this,SLOT(atkel_clicked()));
    QObject::connect(visszarak,SIGNAL(clicked()),this,SLOT(visszarak_clicked()));
    QObject::connect(csonakba,SIGNAL(clicked()),this,SLOT(csonakba_clicked()));

    QObject::connect(this,SIGNAL(victory()),parent,SLOT(newgame()));
}
void Game::refresh_pics()
{
    csonak_pic->setPixmap(rcm->get_csonak(QString("csonak%1").arg(csonak_szam))->scaled(QSize(200,150)));
    mkbal_pic->setPixmap(rcm->get_fold(QString("fold%1").arg(bal_szam))->scaled(QSize(200,150)));
    mkjobb_pic->setPixmap(rcm->get_fold(QString("fold%1").arg(jobb_szam))->scaled(QSize(200,150)));
}

void Game::atkel_clicked()
{
    if(csonak_szam > 0)
    {
        if(irany == cb_text1)//balról jobbra
        {
            jobb_szam += csonak_szam;
            csonak_szam = 0;
            refresh_pics();
        }
        else
        {
            bal_szam += csonak_szam;
            csonak_szam = 0;
            refresh_pics();
        }
        irany = "";
        ++lepes_szam;
        if(mknum == jobb_szam)
        {
            QMessageBox qmsg;
            qmsg.setText((QString(QObject::trUtf8("Gratulálok %1 átkeléssel oldottad meg!")).arg(lepes_szam)));
            qmsg.exec();
            emit victory();
        }
    }
    else
    {
        QMessageBox qmsg;
        qmsg.setText(QObject::trUtf8("Nincs senki a csónakban"));
        qmsg.exec();
    }
}
void Game::visszarak_clicked()
{
    if(csonak_szam > 0)
    {
        if(irany == cb_text1)//balról jobbra
        {
            bal_szam += csonak_szam;
            csonak_szam = 0;
            refresh_pics();
        }
        else
        {
            jobb_szam += csonak_szam;
            csonak_szam = 0;
            refresh_pics();
        }
        irany = "";
    }
    else
    {
        QMessageBox qmsg;
        qmsg.setText(QObject::trUtf8("Nincs senki a csónakban"));
        qmsg.exec();
    }
}

void Game::csonakba_clicked()
{
    if(knum > csonak_szam)
    {
        int val = csonak_slider->value();
        QString oldal = baljobb_cb->currentText();
        if(oldal == irany || irany == "")
        {
            if(irany == "")
                irany = oldal;
            if(oldal == cb_text1 && bal_szam >= val)//balról jobbra
            {
                csonak_szam += val;
                bal_szam -= val;
                refresh_pics();
            }
            else if(oldal == cb_text2 && jobb_szam >= val)//jobbról balra
            {
                csonak_szam += val;
                jobb_szam -= val;
                refresh_pics();
            }
            else
            {//ha slider-en tobbet adna meg mint amenyi ember van az adott oldalon
                QMessageBox qmsg;
                qmsg.setText(QObject::trUtf8("Nincs annyi ember az adott oldalon."));
                qmsg.exec();
            }
        }
        else
        {//ha masik oldalrol akarna csonakba rakni embert
            QMessageBox qmsg;
            qmsg.setText("Egyszerre nem szálhatnak fel mind 2 oldalról");
            qmsg.exec();
        }
    }
    else
    {//Ha nincs hely a csonakban
        QMessageBox qmsg;
        qmsg.setText(QObject::trUtf8("Nincs több hely a csónakban"));
        qmsg.exec();
    }
}
Game::~Game()
{
    QLayoutItem *child;
    while ((child = game_layout->takeAt(0)) != 0)
    {
        delete child->widget();
    }
    main_layout->removeItem(game_layout);
    delete game_layout;
}
