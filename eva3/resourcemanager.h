#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
enum class Field
{
    Blue,
    Red
};

#include <QVector>
class ResourceManager
{
public:
    ResourceManager();
    bool save_game(int n,
                   int turn,
                   int will_come_again,
                   int blue_coll,
                   QVector<int>& blue_fields,
                   int red_coll,
                   QVector<int>& red_fields);
    bool load_game(int& n,
                   Field& turn,
                   bool& will_come_again,
                   int& blue_coll,
                   QVector<int>& blue_fields,
                   int& red_coll,
                   QVector<int>& red_fields);
};

#endif // RESOURCEMANAGER_H
