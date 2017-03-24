#include "resourcemanager.h"
#include <QDir>

//p playerid xdir ydir
ResourceManager::ResourceManager()
{
    QStringList filters;
    filters << "*.jpg";
    foreach(const QString& imgname, QDir(":/images").entryList(filters))
    {
        pictures[imgname.left(imgname.length()-4)] = new QPixmap(QString(":/images/%1").arg(imgname));
    }
}

const QPixmap* ResourceManager::get_picture(QString key)const
{
    QMap<QString,QPixmap*>::const_iterator tmp = pictures.find(key);
    return tmp.value();
}

ResourceManager::~ResourceManager()
{
    for(QMap<QString,QPixmap*>::iterator it = pictures.begin(); it != pictures.end(); ++it)
    {
        delete it.value();
    }
}
