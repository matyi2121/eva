#include "game.h"

Game::Game(QWidget* Parent,int Mknum,int Knum,QGridLayout* Main_layout, ResourceManager* Rcm)
    :QWidget(Parent),
     parent(Parent),
     main_layout(Main_layout),
     mknum(Mknum),
     knum(Knum),
     rcm(Rcm),
     cb_text1(QObject::trUtf8("balról jobbra")),
     cb_text2(QObject::trUtf8("jobbról balra")),
     lepes_szam(0),
     irany(""),
     balk_szam(Mknum),
     balm_szam(Mknum),
     csonakk_szam(0),
     csonakm_szam(0),
     jobbk_szam(0),
     jobbm_szam(0)
{
    init_window();
}

void Game::init_window()
{
    //A játékablak felépítése
    game_layout = new QGridLayout;
    game_layout->setHorizontalSpacing(0);
    game_layout->setVerticalSpacing(0);
    new_game = new QPushButton(QObject::trUtf8("Új játék"),this);

    //Bal oszlop
    baljobb_cb = new QComboBox(this);
    baljobb_cb->addItem(cb_text1);
    baljobb_cb->addItem(cb_text2);
    game_layout->addWidget(baljobb_cb,0,0);

    csonakk_lb = new QLabel("Hány kannibál menjen a csónakba?");
    csonakk_lb->setWordWrap(true);
    game_layout->addWidget(csonakk_lb,1,0);

    csonakk_slider = new QSlider(Qt::Horizontal,this);
    csonakk_slider->setMinimum(0);
    csonakk_slider->setMaximum(5);
    csonakk_slider->setValue(0);
    game_layout->addWidget(csonakk_slider,2,0);

    csonakm_lb = new QLabel("Hány misszionárius menjen a csónakba?");
    csonakm_lb->setWordWrap(true);
    game_layout->addWidget(csonakm_lb,3,0);

    csonakm_slider = new QSlider(Qt::Horizontal,this);
    csonakm_slider->setMinimum(0);
    csonakm_slider->setMaximum(5);
    csonakm_slider->setValue(0);
    game_layout->addWidget(csonakm_slider,4,0);

    bal_part = new QLabel("bal part");
    game_layout->addWidget(bal_part,5,0);

    mbal_pic = new QLabel(this);
    mbal_pic->setPixmap(rcm->get_pics(QString("mfold%1").arg(balm_szam))->scaled(200,150));
    game_layout->addWidget(mbal_pic,7,0);

    kbal_pic = new QLabel(this);
    kbal_pic->setPixmap(rcm->get_pics(QString("kfold%1").arg(balk_szam))->scaled(200,150));
    game_layout->addWidget(kbal_pic,8,0);
    //kozep
    csonakk_lcd = new QLCDNumber(1,this);
    csonakk_lcd->display(0);
    game_layout->addWidget(csonakk_lcd,2,1);

    csonakm_lcd = new QLCDNumber(1,this);
    csonakm_lcd->display(0);
    game_layout->addWidget(csonakm_lcd,4,1);

    csonakm_pic = new QLabel(this);
    csonakm_pic->setPixmap(rcm->get_pics(QString("mcsonak%1").arg(csonakm_szam))->scaled(QSize(200,150)));
    game_layout->addWidget(csonakm_pic,8,1);

    csonakk_pic = new QLabel(this);
    csonakk_pic->setPixmap(rcm->get_pics(QString("kcsonak%1").arg(csonakk_szam))->scaled(QSize(200,150)));
    game_layout->addWidget(csonakk_pic,8,2);
    //jobb
    game_layout->addWidget(new_game,0,3);

    csonakba = new QPushButton(QObject::trUtf8("Csónakba rak"));
    game_layout->addWidget(csonakba,1,3);

    visszarak = new QPushButton(QObject::trUtf8("Visszarak"));
    game_layout->addWidget(visszarak,2,3);

    atkel = new QPushButton(QObject::trUtf8("Átkel"));
    game_layout->addWidget(atkel,3,3);

    jobb_part = new QLabel("jobb part");
    game_layout->addWidget(jobb_part,5,3);

    mjobb_pic = new QLabel(this);
    mjobb_pic->setPixmap(rcm->get_pics(QString("mfold%1").arg(jobbm_szam))->scaled(200,150));
    game_layout->addWidget(mjobb_pic,7,3);

    kjobb_pic = new QLabel(this);
    kjobb_pic->setPixmap(rcm->get_pics(QString("kfold%1").arg(jobbk_szam))->scaled(200,150));
    game_layout->addWidget(kjobb_pic,8,3);

    main_layout->addLayout(game_layout,0,0);

    QObject::connect(new_game,SIGNAL(clicked()),parent,SLOT(newgame()));
    QObject::connect(csonakk_slider,SIGNAL(valueChanged(int)),csonakk_lcd,SLOT(display(int)));
    QObject::connect(csonakm_slider,SIGNAL(valueChanged(int)),csonakm_lcd,SLOT(display(int)));
    QObject::connect(atkel,SIGNAL(clicked()),this,SLOT(atkel_clicked()));
    QObject::connect(visszarak,SIGNAL(clicked()),this,SLOT(visszarak_clicked()));
    QObject::connect(csonakba,SIGNAL(clicked()),this,SLOT(csonakba_clicked()));

    QObject::connect(this,SIGNAL(victory()),parent,SLOT(newgame()));
}
void Game::refresh_pics()
{
    csonakk_pic->setPixmap(rcm->get_pics(QString("kcsonak%1").arg(csonakk_szam))->scaled(QSize(200,150)));
    csonakm_pic->setPixmap(rcm->get_pics(QString("mcsonak%1").arg(csonakm_szam))->scaled(QSize(200,150)));
    mbal_pic->setPixmap(rcm->get_pics(QString("mfold%1").arg(balm_szam))->scaled(QSize(200,150)));
    kbal_pic->setPixmap(rcm->get_pics(QString("kfold%1").arg(balk_szam))->scaled(QSize(200,150)));
    mjobb_pic->setPixmap(rcm->get_pics(QString("mfold%1").arg(jobbm_szam))->scaled(QSize(200,150)));
    kjobb_pic->setPixmap(rcm->get_pics(QString("kfold%1").arg(jobbk_szam))->scaled(QSize(200,150)));
}

bool Game::check_lose_cond(int balk,int balm, int csonakk, int csonakm, int jobbk, int jobbm)const
{
    bool retVal = false;
    if(balk > balm && balm != 0)
    {
        retVal = true;
    }
    else if(csonakk > csonakm && csonakm != 0)
    {
        retVal = true;
    }
    else if(jobbk > jobbm && jobbm != 0)
    {
        retVal = true;
    }
    return retVal;
}

/*
 * Abban az esetben, ha vannak a csónakban, átjuttatja őket a másik oldalra,
 * hogy ha nem halnak meg közben a misszionáriusok valamelyik oldalon.
*/
void Game::atkel_clicked()
{
    QMessageBox qmsg;
    if(csonakk_szam > 0 || csonakm_szam)
    {
        if(irany == cb_text1)//balról jobbra
        {
            if(!check_lose_cond(balk_szam,balm_szam,0,0,jobbk_szam+csonakk_szam,jobbm_szam+csonakm_szam))
            {
                jobbk_szam += csonakk_szam;
                jobbm_szam += csonakm_szam;
                csonakk_szam = 0;
                csonakm_szam = 0;
                refresh_pics();
                irany = "";
                ++lepes_szam;
            }
            else
            {
                qmsg.setText(QObject::trUtf8("Az adott lépés a valamelyik oldalon a misszionáriusok halálát okozná!"));
                qmsg.exec();
            }
        }
        else
        {
            if(!check_lose_cond(balk_szam+csonakk_szam,balm_szam+csonakm_szam,0,0,jobbk_szam,jobbm_szam))
            {
                balk_szam += csonakk_szam;
                balm_szam += csonakm_szam;
                csonakk_szam = 0;
                csonakm_szam = 0;
                refresh_pics();
                irany = "";
                ++lepes_szam;
            }
            else
            {
                qmsg.setText(QObject::trUtf8("Az adott lépés a valamelyik oldalon a misszionáriusok halálát okozná!"));
                qmsg.exec();
            }

        }

        if(2*mknum == jobbk_szam+jobbm_szam)
        {
            qmsg.setText((QString(QObject::trUtf8("Gratulálok %1 átkeléssel oldottad meg!")).arg(lepes_szam)));
            qmsg.exec();
            emit victory();
        }
    }
    else
    {
        qmsg.setText(QObject::trUtf8("Nincs senki a csónakban"));
        qmsg.exec();
    }
}
//Megnézi, hogy vannak-e a csónakban, és ha igen akkor visszateszi a megfelelő oldalra őket.
void Game::visszarak_clicked()
{
    if(csonakk_szam > 0 || csonakm_szam > 0)
    {
        if(irany == cb_text1)//balról jobbra
        {
            balk_szam += csonakk_szam;
            csonakk_szam = 0;
            balm_szam += csonakm_szam;
            csonakm_szam = 0;
            refresh_pics();
        }
        else
        {
            jobbk_szam += csonakk_szam;
            csonakk_szam = 0;
            jobbm_szam += csonakm_szam;
            csonakm_szam = 0;
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
/*
 *Ellenőrzések:
 * 1. Abban az esetben, ha vannak már a csónakba, akkor ugyan abból az irányból akar még a csónakba rakni?
 * 2. Van-e annyi m-k amennyit a csónakba akar rakni az adott oldalon?
 * 3. Van-e elég hely a csónakban?
 * 4. Meghalnának-e a m-ok valahol, ha megtennénk az adott lépést?
 *Ha nem volt az ellenőrzéseknél probléma, akkor:
 * 1, Megnézni merről rakjuk be a csónakra az embereket, ha még nem lett az irány beállítva beállítjuk.
 * 2, Kellő számú m-k-t levonni adott oldalról és csónakhoz adni.
 * 3, Képek frissítése
 */
void Game::csonakba_clicked()
{
    QString oldal = baljobb_cb->currentText();
    int kval = csonakk_slider->value();
    int mval = csonakm_slider->value();
    QMessageBox qmsg;
    bool felfer = (knum - (csonakk_szam+csonakm_szam+kval+mval)) >= 0;
    if(irany == "" || oldal == irany)//1.
    {
        if(felfer)//3.
        {
            if(oldal == cb_text1 && balk_szam >= kval && balm_szam >= mval)//2-1.
            {
                if(!check_lose_cond(balk_szam-kval,balm_szam-mval,csonakk_szam+kval,csonakm_szam+mval,jobbk_szam,jobbm_szam))//4.
                {
                    if(irany == "")//1,
                    {
                        irany = oldal;
                    }
                    //2,
                    balk_szam -= kval;
                    csonakk_szam += kval;
                    balm_szam -= mval;
                    csonakm_szam += mval;
                    //
                    refresh_pics();//3,
                }
                else
                {
                    qmsg.setText(QObject::trUtf8("Az adott lépés a valamelyik oldalon vagy a csónakban a misszionáriusok halálát okozná!"));
                    qmsg.exec();
                }
            }
            else if(oldal == cb_text2 && jobbk_szam >= kval && jobbm_szam >= mval)//2-2.
            {
                if(!check_lose_cond(balk_szam,balm_szam,csonakk_szam+kval,csonakm_szam+mval,jobbk_szam-kval,jobbm_szam-mval))//4.
                {
                    if(irany == "")//1,
                    {
                        irany = oldal;
                    }
                    //2,
                    jobbk_szam -= kval;
                    csonakk_szam += kval;
                    jobbm_szam -= mval;
                    csonakm_szam += mval;
                    //
                    refresh_pics();//3,
                }
                else
                {
                    qmsg.setText(QObject::trUtf8("Az adott lépés a valamelyik oldalon vagy a csónakban a misszionáriusok halálát okozná!"));
                    qmsg.exec();
                }
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
        qmsg.setText(QObject::trUtf8("Egyszerre nem lehet a csónakba rakni mind 2 irányból!"));
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
