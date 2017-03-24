#ifndef START_H
#define START_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>

class StartView : public QWidget
{
    Q_OBJECT
public:
    StartView(QGridLayout* Main_layout,QWidget *parent = 0);
    ~StartView();
private:
    QWidget* parent;
    QGridLayout* main_layout;
    QComboBox* size_cb;
    QPushButton* start_button;
    const int smallest_n;
    int n;
signals:

public slots:
};

#endif // START_H
