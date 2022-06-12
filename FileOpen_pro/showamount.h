#ifndef SHOWAMOUNT_H
#define SHOWAMOUNT_H

#include <QDialog>
#include <QStandardItemModel>

#include "hospitals.h"

namespace Ui {
class ShowAmount;
}

class ShowAmount : public QDialog
{
    Q_OBJECT

public:
    explicit ShowAmount(QWidget *parent = nullptr);
    ~ShowAmount();

public:
    void SaveFileName(QString filename);
    QString fileNameSaved;

protected:

    Hospitals* _hospitals;

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    Ui::ShowAmount *ui;
    QStandardItemModel * model_amount;
};

#endif // SHOWAMOUNT_H
