#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include<QPixmap>
#include<QMap>
class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();
    const QPixmap* get_picture(QString key)const;
    enum class Exceptions
    {
        NO_SUCH_PICTURE
    };

private:
    QMap<QString,QPixmap*> pictures;
};

#endif // RESOURCEMANAGER_H
