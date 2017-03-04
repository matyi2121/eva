#ifndef START_H
#define START_H

#include <QWidget>
#include <QSlider>
#include <QLCDNumber>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

class Start
{
public:
    Start(QWidget* Parent,QGridLayout* Main_layout);
    ~Start();
    int k_num()const;
    int mk_num()const;
private:
    void init_window();
    QWidget* parent;
    QGridLayout* main_layout;

    QGridLayout* start_layout;

    QLabel* mk_label;
    QSlider* mk_slider;
    QLCDNumber* mk_lcd;

    QLabel* k_label;
    QSlider* k_slider;
    QLCDNumber* k_lcd;

    QString start_text;
    QPushButton* start_button;
};

#endif // START_H
