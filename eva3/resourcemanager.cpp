#include "resourcemanager.h"
#include <QFile>
#include <QTextStream>
ResourceManager::ResourceManager(){}

bool ResourceManager::save_game(int n,
                                int turn,
                                int wcm,
                                int blue_coll,
                                QVector<int>& blue_fields,
                                int red_coll,
                                QVector<int>& red_fields)
{
    QFile file("game.sav");
    if (!file.open(QFile::WriteOnly))
            return false;
    QTextStream stream(&file);

    stream << n << endl;
    stream << turn << endl;
    stream << wcm << endl;
    stream << blue_coll << endl;
    for(int i = 0; i < n; ++i)
    {
        stream << blue_fields[i] << endl;
    }

    stream << red_coll << endl;
    for(int i = 0; i < n; ++i)
    {
        stream << red_fields[i] << endl;
    }
    file.close();
    return true;
}

bool ResourceManager::load_game(int& n,
                                Field& turn,
                                bool& will_come_again,
                                int& blue_coll,
                                QVector<int>& blue_fields,
                                int& red_coll,
                                QVector<int>& red_fields)
{
    QFile file("game.sav");
    if(!file.open(QFile::ReadOnly))
        return false;

    QTextStream stream(&file);

    n = stream.readLine().toInt();
    int t = stream.readLine().toInt();
    if(t == 1)
    {
        turn = Field::Blue;
    }
    else
    {
        turn = Field::Red;
    }

    int l = stream.readLine().toInt();
    if(l == 1)
    {
        will_come_again = true;
    }
    else
    {
        will_come_again = false;
    }

    blue_fields.resize(n);
    red_fields.resize(n);
    blue_coll = stream.readLine().toInt();
    for(int i = 0; i < n; ++i)
    {
        blue_fields[i] = stream.readLine().toInt();
    }

    red_coll = stream.readLine().toInt();
    for(int i = 0; i < n; ++i)
    {
        red_fields[i] = stream.readLine().toInt();
    }

    file.close();
    return true;
}
