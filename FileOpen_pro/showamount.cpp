#include "showamount.h"
#include "mainwindow.h"
#include "ui_showamount.h"

#include <QMessageBox>

ShowAmount::ShowAmount(QWidget *parent)
    : QDialog(parent)
    , _hospitals(new Hospitals(this))
    , ui(new Ui::ShowAmount)
{
    ui->setupUi(this);
}



ShowAmount::~ShowAmount()
{
    delete ui;
}


// Closing Widget
void ShowAmount::on_pushButton_3_clicked()
{
    QWidget::close();
}

// Saving FileName
void ShowAmount::SaveFileName(QString filename){
    fileNameSaved = filename;
}

// Showing Amount City
void ShowAmount::on_pushButton_2_clicked()
{
        ui->label->setText("<b>Amount of hospitals in CITIES:<b>");

        if(_hospitals->openFile(ShowAmount::fileNameSaved))
        {
            /// filling table
            QMap<QString, Clinic*> copyMapClinics = _hospitals->getMapClinicsData();
            QMap<QString, int> mapAmountCity;
            QModelIndex index;
            int row = 0;

            for (Clinic * item : copyMapClinics){
                ++mapAmountCity[item->city];
            }



            /// declaring table size + headers
            model_amount = new QStandardItemModel(mapAmountCity.size(), 2, this);
            model_amount->setHeaderData(0, Qt::Horizontal, "City");
            model_amount->setHeaderData(1, Qt::Horizontal, "Amount");


            for (auto p = mapAmountCity.begin(); p != mapAmountCity.end(); ++p){

                index = model_amount->index(row,0);
                model_amount->setData(index, p.key());

                index = model_amount->index(row,1);
                model_amount->setData(index, p.value());

                ++row;
            }


            /// printing table
            ui->tableView->setModel(model_amount);
        }


}


// Showing Amount State
void ShowAmount::on_pushButton_clicked()
{
    ui->label->setText("<b>Amount of hospitals in STATES:<b>");

    if(_hospitals->openFile(ShowAmount::fileNameSaved))
    {
        /// filling table
        QMap<QString, Clinic*> copyMapClinics = _hospitals->getMapClinicsData();
        QMap<QString, int> mapAmountState;
        QModelIndex index;
        int row = 0;

        for (Clinic * item : copyMapClinics){
            ++mapAmountState[item->state];
        }



        /// declaring table size + headers
        model_amount = new QStandardItemModel(mapAmountState.size(), 2, this);
        model_amount->setHeaderData(0, Qt::Horizontal, "State");
        model_amount->setHeaderData(1, Qt::Horizontal, "Amount");


        for (auto p = mapAmountState.begin(); p != mapAmountState.end(); ++p){

            index = model_amount->index(row,0);
            model_amount->setData(index, p.key());

            index = model_amount->index(row,1);
            model_amount->setData(index, p.value());

            ++row;
        }


        /// printing table
        ui->tableView->setModel(model_amount);
    }
}

