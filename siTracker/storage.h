#ifndef STORAGE_H
#define STORAGE_H

#include "coin.h"

#include <QFileDialog>
#include <QMap>



// Storage Class
class Storage
{

public:
    // Constructor + Desctructor
    Storage();

    // Methods
    QMap<QString, Coin> LoadData(QFile &file);


protected:
    // Childrens
    Coin *_coin;


};

#endif // STORAGE_H
