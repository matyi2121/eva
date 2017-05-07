#ifndef RESOURCEMANAGER_MOCK
#define RESOURCEMANAGER_MOCK
#include "resourcemanager.h"
#include <QDebug>
class ResourceManager_Mock : public ResourceManager
{
public:
    ResourceManager_Mock(){}
    bool save_game(int n,
                   int turn,
                   int count_same_turns,
                   int blue_coll,
                   QVector<int>& blue_fields,
                   int red_coll,
                   QVector<int>& red_fields)
    {
        qDebug() << "Sikeres mentes.";

        qDebug() << "Meret:" << n;

        if(turn == 1)
            qDebug() << "A kovetkezo jatekos:Kek";
        else qDebug() << "A kovetkezo jatekos:Piros";

        if(count_same_turns == 1)
            qDebug() << "Masodjara jon:Igaz";
        else qDebug() << "Masodjara jon:Hamis";

        qDebug() << "A kek gyujtotalban levo kavicsok szama:" << blue_coll;

        QString out = "( ";
        for(int i = 0; i < n; ++i)
        {
            out += QString::number(blue_fields[i]) + " ";
        }
        out += ")";
        qDebug() << "A kek talakban levo kovek:" << out;

        qDebug() << "A piros gyujtotalban levo kavicsok szama:" << red_coll;

        out = "( ";
        for(int i = 0; i < n; ++i)
        {
            out += QString::number(red_fields[i]) + " ";
        }
        out += ")";
        qDebug() << "A piros talakban levo kovek:" << out;
        return true;
    }

    bool load_game(int& n,
                   Field& turn,
                   int& count_same_turns,
                   int& blue_coll,
                   QVector<int>& blue_fields,
                   int& red_coll,
                   QVector<int>& red_fields)
    {
        n = 4;
        turn = Field::Red;
        count_same_turns = 0;
        blue_coll = 0;
        blue_fields[0] = 6;
        blue_fields[1] = 0;
        blue_fields[2] = 7;
        blue_fields[3] = 7;
        red_coll = 1;
        red_fields[0] = 6;
        red_fields[1] = 7;
        red_fields[2] = 7;
        red_fields[3] = 7;
        qDebug() << "Sikeres betoltes.";

        qDebug() << "Meret:" << n;

        if(turn == Field::Blue)
            qDebug() << "A kovetkezo jatekos:Kek";
        else qDebug() << "A kovetkezo jatekos:Piros";

        if(count_same_turns == 1)
            qDebug() << "Masodjara jon:Igaz";
        else qDebug() << "Masodjara jon:Hamis";

        qDebug() << "A kek gyujtotalban levo kavicsok szama:" << blue_coll;

        QString out = "( ";
        for(int i = 0; i < n; ++i)
        {
            out += QString::number(blue_fields[i]) + " ";
        }
        out += ")";
        qDebug() << "A kek talakban levo kovek:" << out;

        qDebug() << "A piros gyujtotalban levo kavicsok szama:" << red_coll;

        out = "( ";
        for(int i = 0; i < n; ++i)
        {
            out += QString::number(red_fields[i]) + " ";
        }
        out += ")";
        qDebug() << "A piros talakban levo kovek:" << out;
        return true;
    }
};

#endif // RESOURCEMANAGER_MOCK

