#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <QPixmap>
#include <QMap>
class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();
    const QPixmap* get_csonak(QString key)const
    {
        QMap<QString,QPixmap*>::const_iterator tmp = csonak_pics.find(key);
        return tmp.value();
    }
    QPixmap* get_viz()const
    {
        return viz;
    }
    const QPixmap* get_fold(QString key)const
    {
        QMap<QString,QPixmap*>::const_iterator tmp = fold_pics.find(key);
        return tmp.value();
    }
private:
    QMap<QString,QPixmap*> csonak_pics;
    QMap<QString,QPixmap*> fold_pics;
    QPixmap* viz;
};

#endif // RESOURCEMANAGER_H
