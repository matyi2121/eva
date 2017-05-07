#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include "resourcemanager.h"
#include <QObject>
#include <QVector>
enum class Field
{
    Blue,
    Red
};

class GameModel : public QObject
{
    Q_OBJECT
public:
    explicit GameModel( int N,QObject *parent = 0);
    ~GameModel();
    int get_collector(Field f)const;
    int get_field(Field f,int col)const;
    void empty(int row, int col);
    bool is_empty(int row, int col);
    bool players_turn(Field f);
    bool load_game();
    bool save_game();
private:
    void set_next_player();
    int* next_bowl(int* curr);
    int in(Field f,int* curr);
    int get_size()const;
    void game_over_check();
    bool will_come_again;
    int n;
    Field curr_turn;
    int blue_collector;
    QVector<int> blue_fields;
    int red_collector;
    QVector<int> red_fields;
    ResourceManager rm;
signals:
    void refresh_window();
    void winner(int);
    void size_changed(int);
public slots:
};

#endif // GAMEMODEL_H
