#ifndef HOSPITALS_H
#define HOSPITALS_H


#include <QObject>
#include <QString>
#include <QMap>
#include <QStringListModel>


struct Clinic {
    QString id;
    QString name;
    QString address;
    QString city;
    QString state;

    /// Fills the current object with attributes represented as a string list
    void fill(const QStringList& attrts);

    /// Extracts attributes of the dish as a string list (created new).
    QStringList getInfoAsSList() const;
};



// storage
class Hospitals : public QObject
{
    Q_OBJECT
public:
    explicit Hospitals(QObject *parent = nullptr);
    ~Hospitals();



public:
    /// Opens and read file to internal storage
    bool openFile(const QString& fileName);



public:
    int getMapSize();
    QMap<QString, Clinic*> getMapClinicsData();


protected:
    QMap<QString, Clinic*> _mapClinics;

};

#endif // HOSPITALS_H
