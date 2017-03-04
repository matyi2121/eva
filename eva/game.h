#ifndef GAME_H
#define GAME_H

#include "resourcemanager.h"
#include <QWidget>
#include <QSlider>
#include <QLCDNumber>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>
#include <QMessageBox>

class Game : public QWidget
{
    Q_OBJECT
public:
    Game(QWidget* Parent, int Mknum, int Knum, QGridLayout* Main_layout, ResourceManager* Rcm);
    ~Game();
private:
    void init_window();
    QWidget* parent;
    QGridLayout* main_layout;
    int mknum;
    int knum;
    ResourceManager* rcm;

    QGridLayout* game_layout;

    const QString cb_text1;
    const QString cb_text2;

    QString csonakba_text;
    QString visszarak_text;
    QString atkel_text;
    QString new_game_text;

    //Bal oszlop
    QComboBox* baljobb_cb;
    QLabel* csonak_lb;
    QSlider* csonak_slider;
    QLCDNumber* csonak_lcd;
    QLabel* mkbal_pic;
    //Kozep
    QLabel* folyo_pic;
    QLabel* csonak_pic;
    //Jobb
    QPushButton* new_game;
    QPushButton* csonakba;
    QPushButton* visszarak;
    QPushButton* atkel;
    QLabel* mkjobb_pic;

    //logika
    int lepes_szam;
    QString irany;
    int bal_szam;
    int csonak_szam;
    int jobb_szam;

    void refresh_pics();
private slots:
    void atkel_clicked();
    void visszarak_clicked();
    void csonakba_clicked();
signals:
    void victory();
};

#endif // GAME_H
