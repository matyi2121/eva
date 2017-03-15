#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QString>

class GameManager
{
public:
    GameManager(int Mknum, int Knum);
    ~GameManager();
    bool check_lose_cond()const;
    bool is_boat_empty()const;
    bool to_right()const;
    bool to_left()const;
    bool is_finished()const;
    bool has_place(int cval, int mval)const;
    bool are_enough_on_side(QString side,int cval, int mval)const;
    bool are_enough_on_boat(int cval, int mval)const;

    void arrival(QString side, int cval, int mval);
    void empty_ship();
    void fill_ship(int cval, int mval);

    //getters
    int get_steps()const;
    QString get_dir()const;
    int get_boat_num(char choice)const;
    int get_left_num(char choice)const;
    int get_right_num(char choice)const;
    int get_boat_size()const;

    const QString toright;
    const QString toleft;
private:
    int mknum;
    int knum;
    int step_count;
    QString direction;
    int leftc_num;
    int leftm_num;
    int boatc_num;
    int boatm_num;
    int rightc_num;
    int rightm_num;
};

#endif // GAMEMANAGER_H
