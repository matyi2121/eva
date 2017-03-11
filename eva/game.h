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
    void refresh_layout();

    QWidget* parent;
    QGridLayout* main_layout;
    int mknum;
    int knum;
    ResourceManager* rcm;

    QGridLayout* game_layout;

    //Bal oszlop

    QLabel* csonakk_lb;
    QSlider* csonakk_slider;
    QLCDNumber* csonakk_lcd;

    QLabel* csonakm_lb;
    QSlider* csonakm_slider;
    QLCDNumber* csonakm_lcd;

    QLabel* bal_part;
    QLabel* kbal_pic;
    QLabel* mbal_pic;
    //Kozep
    QLabel* baljobb_lb;

    QLabel* leszallk_lb;
    QSlider* leszallk_slider;
    QLCDNumber* leszallk_lcd;
    QLabel* leszallm_lb;
    QSlider* leszallm_slider;
    QLCDNumber* leszallm_lcd;

    QLabel* csonakk_pic;
    QLabel* csonakm_pic;
    //Jobb
    QPushButton* new_game;
    QPushButton* csonakba;
    QPushButton* visszarak;
    QPushButton* atkel;
    QLabel* jobb_part;
    QLabel* kjobb_pic;
    QLabel* mjobb_pic;

    //logika
    const QString jobbra;
    const QString balra;
    int lepes_szam;
    QString irany;
    int balk_szam;
    int balm_szam;
    int csonakk_szam;
    int csonakm_szam;
    int jobbk_szam;
    int jobbm_szam;
    bool check_lose_cond(int balk,int balm, int csonakk, int csonakm, int jobbk, int jobbm)const;

private slots:
    void atkel_clicked();
    void visszarak_clicked();
    void csonakba_clicked();
signals:
    void victory();
};

#endif // GAME_H
