#include "resourcemanager.h"

ResourceManager::ResourceManager()
{
    for(int i = 0; i < 6; ++i)
    {
        pics[QString("kcsonak%1").arg(i)] = new QPixmap(QString(":images/kcsonak%1.jpg").arg(i));
        pics[QString("mcsonak%1").arg(i)] = new QPixmap(QString(":images/mcsonak%1.jpg").arg(i));
        pics[QString("kfold%1").arg(i)] = new QPixmap(QString(":images/kfold%1.jpg").arg(i));
        pics[QString("mfold%1").arg(i)] = new QPixmap(QString(":images/mfold%1.jpg").arg(i));
    }
}

ResourceManager::~ResourceManager()
{
    for(QMap<QString,QPixmap*>::iterator i = pics.begin(); i != pics.end(); ++i)
    {
        delete i.value();
    }
}

const QPixmap* ResourceManager::get_pics(QString key)const
{
    QMap<QString,QPixmap*>::const_iterator tmp = pics.find(key);
    if(tmp != pics.end())
    {
        return tmp.value();
    }
    else
    {
        return NULL;
    }
}
