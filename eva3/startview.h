#ifndef STARTVIEW_H
#define STARTVIEW_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>


class StartView : public QWidget
{
    Q_OBJECT
public:
    explicit StartView(QGridLayout* Main_layout, QWidget *parent = 0);
    ~StartView();
private:
    QWidget* parent;
    QGridLayout* main_layout;
    QComboBox* size_cb;
    QPushButton* start_button;
    QPushButton* load_button;
    const int smallest_n;
    int n;
signals:

public slots:
};

#endif // STARTVIEW_H
