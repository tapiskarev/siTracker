#include "hospitals.h"
#include "mainwindow.h"

#include <stdexcept>

#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QString>



Hospitals::Hospitals(QObject *parent)
    : QObject{parent}
{

}

// Destructor
Hospitals::~Hospitals()
{

    for (const auto& clinicPair : _mapClinics)
    {
        delete clinicPair;
    }
    _mapClinics.clear();
}



// Splitting String
QVector<QString> split(const QString& str){

    // declaring item string to store the current "word" upto del + returning vector with items
    QString item;
    QVector<QString> lineVector;
    // declaring index of quoted line
    int quoted_line_index = 0;

    for(QChar i : str){


        // Char is NOT , or "
        if(i != ',' and i != '"'){
            item += i;
        }
        // Char is , or "
        else{
            // Char is ,
            if (i == ','){

                if (quoted_line_index == 0){
                    lineVector.push_back(item);
                    item = "";
                }else{
                    item += i;
                }
            }
            // char is "
            else{
                // opening quote
                if (item.isEmpty()){
                    item = "";
                    quoted_line_index = 1;
                }
                // closing quote
                else{
                    quoted_line_index = 0;
                }
            }
        }
    }

    lineVector.push_back(item);
    return lineVector;
}


// Opening File + Filling Model
bool Hospitals::openFile(const QString& fileName)
{
    // Mistakes finding
    if (fileName.isEmpty())
        return false;

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly))
    {
        return false;
    }



    // Data reading
    /// first line index
    bool firstLine = true;


    QTextStream fStream(&file);
    while (!fStream.atEnd())
    {
        QString line = fStream.readLine();

        if (!line.isNull() && !firstLine)
        {
            /// spliting line by items
            QVector<QString> lineVector = split(line);

            /// checking the size of line
            if(lineVector.size() < 34)
                throw std::runtime_error("Record not valid");

            /// importing struct
            Clinic *& curClinic = _mapClinics[lineVector[4]];
            if (!curClinic)
                curClinic = new Clinic();

            ///curDish->fill(textDescr);
            _mapClinics[lineVector[4]] = curClinic;


            curClinic->name = lineVector[4];
            curClinic->id = lineVector[2];
            curClinic->address = lineVector[5];
            curClinic->city = lineVector[6];
            curClinic->state = lineVector[7];

        }
        else
            firstLine = false;
    }

    /// closing file
    file.close();


    // Model filling
    ///listing names
    QList<QString> names = _mapClinics.keys();

    ///listing addresses, ids, ...
    QList<QString> addresses;
    QList<QString> ids;
    QList<QString> cities;
    QList<QString> states;


    for (Clinic * cl : _mapClinics){

        addresses.append(cl->address);
        ids.append(cl->id);
        cities.append(cl->city);
        states.append(cl->state);
    }

    return true;
}


// Getting Map Size
int Hospitals::getMapSize(){

    return _mapClinics.size();
}


// Getting Map Copy
QMap<QString, Clinic*> Hospitals::getMapClinicsData(){
    return _mapClinics;
}
