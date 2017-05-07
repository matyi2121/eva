#include "gamemodel.h"
#include <QMessageBox>
GameModel::GameModel(ResourceManager* RM,int N,QObject *parent)
    : QObject(parent),
      n(N),
      rm(RM)
{
    curr_turn = Field::Blue;
    blue_collector = 0;
    red_collector = 0;
    blue_fields.resize(n);
    red_fields.resize(n);
    for(int i = 0; i < n; ++i)
    {
        blue_fields[i] = 6;
        red_fields[i] = 6;
    }
    will_come_again = false;
}

GameModel::~GameModel()
{
    //dtor
}

int GameModel::get_collector(Field f)const
{
    if(f == Field::Blue)
        return blue_collector;
    else
        return red_collector;
}

int GameModel::get_field(Field f, int col)const
{
    if(f == Field::Blue)
        return blue_fields[col-1];
    else
        return red_fields[col-1];
}

int GameModel::get_size()const
{
    return n;
}

void GameModel::empty(int row, int col)
{
    int adj_col = col-1;

    int* curr = row == 0 ? &blue_fields[adj_col] : &red_fields[adj_col];
    int* start = curr;
    int stones = *curr;
    *curr = 0;

    while(stones > 0)
    {
        curr = next_bowl(curr);
        if(curr != start)
        {
            *curr = *curr + 1;
            --stones;
        }
    }

    int pos = -1;
    if((pos = in(curr_turn,curr)) != -1 && *curr == 1)
    {
        if(curr_turn == Field::Blue)
        {
            blue_collector += *curr + red_fields[pos];
            *curr = 0;
            red_fields[pos] = 0;
        }
        else
        {
            red_collector += *curr + blue_fields[pos];
            *curr = 0;
            blue_fields[pos] = 0;
        }
    }
    else
    {
        if((curr_turn == Field::Blue && curr == &blue_collector) ||
           (curr_turn == Field::Red && curr == &red_collector))
        {
            will_come_again = true;
        }
    }
    emit refresh_window();
    game_over_check();
    set_next_player();
}

bool GameModel::is_empty(int row, int col)
{
    if(row == 0)
        return blue_fields[col-1] == 0;
    else
        return red_fields[col-1] == 0;
}

bool GameModel::players_turn(Field f)
{
    return f == curr_turn;
}

void GameModel::set_next_player()
{
    if(will_come_again)
    {
        will_come_again = false;
    }
    else
    {
        curr_turn = curr_turn == Field::Blue ? Field::Red : Field::Blue;
    }
}


int* GameModel::next_bowl(int* curr)
{
    int* ret = NULL;
    if(curr == &blue_collector)
    {
        ret = &blue_fields[0];
    }
    else if(curr == &red_collector)
    {
        ret = &red_fields[n-1];
    }
    else
    {
        int pos;
        if((pos = in(Field::Blue, curr)) != -1)
        {
            if(curr == &blue_fields[n-1])
            {
                ret = &red_collector;
            }
            else
            {
                ret = &blue_fields[pos+1];
            }
        }
        else if((pos = in(Field::Red, curr)) != -1)
        {
            if(curr == &red_fields[0])
            {
                ret = &blue_collector;
            }
            else
            {
                ret = &red_fields[pos-1];
            }
        }
    }
    return ret;
}

int GameModel::in(Field f,int* curr)
{
    int ret = -1;
    QVector<int>* to_check;
    if(f == Field::Blue)
    {
        to_check = &blue_fields;
    }
    else
    {
        to_check = &red_fields;
    }
    int i = 0;
    while(i < n && ret == -1)
    {
        const int* check = &to_check->at(i);
        if(curr == check)
        {
            ret = i;
        }
        ++i;
    }
    return ret;
}

void GameModel::game_over_check()
{
    int blues = 0;
    int reds = 0;
    for(int i = 0; i < n; ++i)
    {
        blues += blue_fields[i];
        reds += red_fields[i];
    }
    if(blues == 0 || reds == 0)
    {
        int to_emit = 0;
        if(blue_collector > red_collector)
        {
            to_emit = 1;
        }
        else if(red_collector > blue_collector)
        {
            to_emit = 2;
        }
        emit winner(to_emit);
    }
}

bool GameModel::load_game()
{
    int in_size = 0;
    bool ret = false;
    if(rm->load_game(in_size,
                    curr_turn,
                    will_come_again,
                    blue_collector,
                    blue_fields,
                    red_collector,
                    red_fields))
    {
        if(in_size != n)
        {
            emit size_changed(in_size);
            n=in_size;
        }
        emit refresh_window();
        ret = true;
    }
    return ret;
}

bool GameModel::save_game()
{
    bool ret = false;
    int turn = curr_turn == Field::Blue ? 1 : 2;
    int wca = will_come_again == true ? 1 : 0;
    if(rm->save_game(n,
                     turn,
                     wca,
                     blue_collector,
                     blue_fields,
                     red_collector,
                     red_fields))
    {
        ret = true;
    }
    return ret;
}
