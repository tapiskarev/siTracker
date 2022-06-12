#ifndef EDIT_H
#define EDIT_H

#include <QDialog>
#include <QMessageBox>
#include <fstream>
#include <string>
#include <QVector>

#include "hospitals.h"

namespace Ui {
class Edit;
}

class Edit : public QDialog
{
    Q_OBJECT

public:
    explicit Edit(QWidget *parent = nullptr);
    ~Edit();

public:
    void SaveFileName(QString filename);
    QString fileNameSaved;


private slots:


    void on_pushButton_clicked();

    void on_button_add_clicked();

    void on_button_delete_clicked();

protected:

    Hospitals* _hospitals;


private:
    Ui::Edit *ui;
};

#endif // EDIT_H
