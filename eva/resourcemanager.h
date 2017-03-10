#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <QPixmap>
#include <QMap>
class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();
    const QPixmap* get_pics(QString key)const;
private:
    QMap<QString,QPixmap*> pics;
};

#endif // RESOURCEMANAGER_H
