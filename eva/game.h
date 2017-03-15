#ifndef GAME_H
#define GAME_H

#include "resourcemanager.h"
#include "gamemanager.h"
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
    void left_col();
    void mid_col();
    void right_col();
    void refresh_layout();

    QWidget* parent;
    const char cann;
    const char miss;
    QGridLayout* main_layout;

    ResourceManager* rcm;
    GameManager* gm;

    //left oszlop

    QLabel* boatc_lb;
    QSlider* boatc_slider;
    QLCDNumber* boatc_lcd;

    QLabel* boatm_lb;
    QSlider* boatm_slider;
    QLCDNumber* boatm_lcd;

    QLabel* left_part;
    QLabel* cleft_pic;
    QLabel* mleft_pic;
    //Kozep
    QLabel* leftright_lb;

    QLabel* get_offc_lb;
    QSlider* get_offc_slider;
    QLCDNumber* get_offc_lcd;
    QLabel* get_offm_lb;
    QSlider* get_offm_slider;
    QLCDNumber* get_offm_lcd;

    QLabel* boatc_pic;
    QLabel* boatm_pic;
    //right
    QPushButton* new_game;
    QPushButton* into_boat;
    QPushButton* put_back;
    QPushButton* ferry;
    QLabel* right_part;
    QLabel* kright_pic;
    QLabel* mright_pic;

private slots:
    void ferry_clicked();
    void put_back_clicked();
    void into_boat_clicked();
signals:
    void victory();
};

#endif // GAME_H
