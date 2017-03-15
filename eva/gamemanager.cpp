#include "gamemanager.h"

GameManager::GameManager(int Mknum, int Knum)
    :toright(QObject::trUtf8("jobbra")),
     toleft(QObject::trUtf8("balra")),
     mknum(Mknum),
     knum(Knum),
     step_count(0),
     direction(toright),
     leftc_num(Mknum),
     leftm_num(Mknum),
     boatc_num(0),
     boatm_num(0),
     rightc_num(0),
     rightm_num(0)
{}

bool GameManager::check_lose_cond()const
{
    bool retVal = false;
    if((direction == toright) &&
       ((leftc_num > leftm_num && leftm_num != 0)|| //check if left side will be safe
       (boatc_num+rightc_num > boatm_num+rightm_num && boatm_num+rightm_num != 0)))//check if right side will be safe
    {
        retVal = true;
    }
    else if((direction == toleft) &&
            ((rightc_num > rightm_num && rightm_num != 0) || //check if right side will be safe
            (boatc_num+leftc_num > boatm_num+leftm_num && boatm_num+leftm_num != 0)))//check if left side will be safe
    {
        retVal = true;
    }
    return retVal;
}

bool GameManager::to_right()const
{
    return direction == toright;
}

bool GameManager::to_left()const
{
    return direction == toleft;
}

bool GameManager::is_boat_empty()const
{
    return boatc_num == 0 && boatm_num == 0;
}

bool GameManager::is_finished()const
{
    return 2*mknum == rightc_num+rightm_num;
}

bool GameManager::are_enough_on_side(QString side,int cval, int mval)const
{
    if(side == toright)
    {
        return rightc_num >= cval && rightm_num >= mval;
    }
    else
    {
        return leftc_num >= cval && leftm_num >= mval;
    }
}

bool GameManager::are_enough_on_boat(int cval, int mval)const
{
    return boatc_num >= cval && boatm_num >= mval;
}

void GameManager::arrival(QString side, int cval, int mval)
{
    if(side == toright)
    {
        rightc_num += cval;
        rightm_num += mval;
        boatc_num -= cval;
        boatm_num -= mval;
        direction = toleft;
    }
    else
    {
        leftc_num += cval;
        leftm_num += mval;
        boatc_num -= cval;
        boatm_num -= mval;
        direction = toright;
    }
    ++step_count;
}

void GameManager::empty_ship()
{
    if(to_right())//balról jobbra
    {
        leftc_num += boatc_num;
        boatc_num = 0;
        leftm_num += boatm_num;
        boatm_num = 0;
    }
    else
    {
        rightc_num += boatc_num;
        boatc_num = 0;
        rightm_num += boatm_num;
        boatm_num = 0;
    }
}

void GameManager::fill_ship(int cval, int mval)
{
    if(to_right())
    {
        leftc_num -= cval;
        boatc_num += cval;
        leftm_num -= mval;
        boatm_num += mval;
    }
    else
    {
        rightc_num -= cval;
        boatc_num += cval;
        rightm_num -= mval;
        boatm_num += mval;
    }
}

int GameManager::get_steps()const
{
    return step_count;
}

QString GameManager::get_dir()const
{
    return direction;
}

int GameManager::get_boat_num(char choice)const
{
    if(choice == 'c')
        return boatc_num;
    else if(choice == 'm')
        return boatm_num;
    return -1;
}

int GameManager::get_left_num(char choice)const
{
    if(choice == 'c')
        return leftc_num;
    else if(choice == 'm')
        return leftm_num;
    return -1;
}

int GameManager::get_right_num(char choice)const
{
    if(choice == 'c')
        return rightc_num;
    else if(choice == 'm')
        return rightm_num;
    return -1;
}

int GameManager::get_boat_size()const
{
    return knum;
}

bool GameManager::has_place(int cval, int mval)const
{
    return (knum - (boatc_num+boatm_num+cval+mval)) >= 0;
}

GameManager::~GameManager()
{

}
