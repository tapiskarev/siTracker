#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>
#include <QStandardItemModel>

#include "hospitals.h"

namespace Ui {
class Search;
}

class Search : public QDialog
{
    Q_OBJECT

public:
    explicit Search(QWidget *parent = nullptr);
    ~Search();

public:
    void SaveFileName(QString filename);
    QString fileNameSaved;

protected:

    Hospitals* _hospitals;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Search *ui;
    QStandardItemModel * model_search;
};

#endif // SEARCH_H
