#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QObject>
#include <QVector>
class ResourceManager : public QObject
{
    Q_OBJECT
public:
    explicit ResourceManager(QObject *parent = 0);
    bool save_game(int n,
                   int blue_coll,
                   QVector<int>& blue_fields,
                   int red_coll,
                   QVector<int>& red_fields);
    bool load_game(int& n,
                   int& blue_coll,
                   QVector<int>& blue_fields,
                   int& red_coll,
                   QVector<int>& red_fields);
signals:

public slots:
};

#endif // RESOURCEMANAGER_H
