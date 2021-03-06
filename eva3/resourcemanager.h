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
                   int count_same_turns,
                   int blue_coll,
                   QVector<int>& blue_fields,
                   int red_coll,
                   QVector<int>& red_fields);
    bool load_game(int& n,
                   Field& turn,
                   int& count_same_turns,
                   int& blue_coll,
                   QVector<int>& blue_fields,
                   int& red_coll,
                   QVector<int>& red_fields);
};

#endif // RESOURCEMANAGER_H
