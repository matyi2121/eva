#include "resourcemanager.h"

ResourceManager::ResourceManager()
{
    for(int i = 0; i < 6; ++i)
    {
        csonak_pics[QString("csonak%1").arg(i)] = new QPixmap(QString(":images/csonak%1.jpg").arg(i));
        fold_pics[QString("fold%1").arg(i)] = new QPixmap(QString(":images/fold%1.jpg").arg(i));
    }
    viz = new QPixmap(":images/viz.jpg");
}

ResourceManager::~ResourceManager()
{
    for(QMap<QString,QPixmap*>::iterator i = csonak_pics.begin(); i != csonak_pics.end(); ++i)
    {
        delete i.value();
    }
    for(QMap<QString,QPixmap*>::iterator i = fold_pics.begin(); i != fold_pics.end(); ++i)
    {
        delete i.value();
    }
    delete viz;
}
