#include "search.h"
#include "mainwindow.h"
#include "ui_search.h"

#include <QMessageBox>

Search::Search(QWidget *parent)
    : QDialog(parent)
    , _hospitals(new Hospitals(this))
    , ui(new Ui::Search)
{
    ui->setupUi(this);
}


Search::~Search()
{
    delete ui;
}

// Saving FileName
void Search::SaveFileName(QString filename){
    fileNameSaved = filename;
}


// Closing Widget
void Search::on_pushButton_clicked()
{
    QWidget::close();
}


void Search::on_pushButton_2_clicked()
{
    /// counting checkmarks
    int check_marks = 0;
    if(ui->checkBox->isChecked()){
        ++check_marks;
    }
    if(ui->checkBox_2->isChecked()){
        ++check_marks;
    }
    if(ui->checkBox_3->isChecked()){
        ++check_marks;
    }


    /// searching with respect to parameter
    if(check_marks == 1){

        /// name search
        if(ui->checkBox->isChecked()){
            if(_hospitals->openFile(Search::fileNameSaved))
            {
                QString search = ui->lineEdit->text();


                /// deleting unsuitable items
                QMap<QString, Clinic*> copyMapClinics = _hospitals->getMapClinicsData();
                QModelIndex index;
                int row = 0;

                for (auto it = copyMapClinics.begin(); it != copyMapClinics.end(); ++it){

                    if(!it.value()->name.contains(search)){
                        copyMapClinics.erase(it);
                    }
                }


                /// declaring table size + headers
                model_search = new QStandardItemModel(copyMapClinics.size(), 5, this);
                model_search->setHeaderData(0, Qt::Horizontal, "ID");
                model_search->setHeaderData(1, Qt::Horizontal, "Name");
                model_search->setHeaderData(2, Qt::Horizontal, "State");
                model_search->setHeaderData(3, Qt::Horizontal, "City");
                model_search->setHeaderData(4, Qt::Horizontal, "Address");

                /// filling model_search
                for (Clinic * item : copyMapClinics){

                    index = model_search->index(row,0);
                    model_search->setData(index, item->id);

                    index = model_search->index(row,1);
                    model_search->setData(index, item->name);

                    index = model_search->index(row,2);
                    model_search->setData(index, item->state);

                    index = model_search->index(row,3);
                    model_search->setData(index, item->city);

                    index = model_search->index(row,4);
                    model_search->setData(index, item->address);

                    ++row;
                }
                /// printing table
                ui->tableView->setModel(model_search);
            }
        }


        /// address search
        else if(ui->checkBox_2->isChecked()){
            if(_hospitals->openFile(Search::fileNameSaved))
            {
                /// reading request + printing it
                QString search = ui->lineEdit->text();


                /// deleting unsuitable items
                QMap<QString, Clinic*> copyMapClinics = _hospitals->getMapClinicsData();
                QModelIndex index;
                int row = 0;

                for (auto it = copyMapClinics.begin(); it != copyMapClinics.end(); ++it){

                    if(!it.value()->address.contains(search)){
                        copyMapClinics.erase(it);
                    }
                }


                /// declaring table size + headers
                model_search = new QStandardItemModel(copyMapClinics.size(), 5, this);
                model_search->setHeaderData(0, Qt::Horizontal, "ID");
                model_search->setHeaderData(1, Qt::Horizontal, "Name");
                model_search->setHeaderData(2, Qt::Horizontal, "State");
                model_search->setHeaderData(3, Qt::Horizontal, "City");
                model_search->setHeaderData(4, Qt::Horizontal, "Address");

                /// filling model_search
                for (Clinic * item : copyMapClinics){

                    index = model_search->index(row,0);
                    model_search->setData(index, item->id);

                    index = model_search->index(row,1);
                    model_search->setData(index, item->name);

                    index = model_search->index(row,2);
                    model_search->setData(index, item->state);

                    index = model_search->index(row,3);
                    model_search->setData(index, item->city);

                    index = model_search->index(row,4);
                    model_search->setData(index, item->address);

                    ++row;
                }
                /// printing table
                ui->tableView->setModel(model_search);
            }
        }

        /// id search
        else if(ui->checkBox_3->isChecked()){
            if(_hospitals->openFile(Search::fileNameSaved))
            {
                /// reading request + printing it
                QString search = ui->lineEdit->text();


                /// deleting unsuitable items
                QMap<QString, Clinic*> copyMapClinics = _hospitals->getMapClinicsData();
                QModelIndex index;
                int row = 0;

                for (auto it = copyMapClinics.begin(); it != copyMapClinics.end(); ++it){

                    if(!it.value()->id.contains(search)){
                        copyMapClinics.erase(it);
                    }
                }


                /// declaring table size + headers
                model_search = new QStandardItemModel(copyMapClinics.size(), 5, this);
                model_search->setHeaderData(0, Qt::Horizontal, "ID");
                model_search->setHeaderData(1, Qt::Horizontal, "Name");
                model_search->setHeaderData(2, Qt::Horizontal, "State");
                model_search->setHeaderData(3, Qt::Horizontal, "City");
                model_search->setHeaderData(4, Qt::Horizontal, "Address");

                /// filling model_search
                for (Clinic * item : copyMapClinics){

                    index = model_search->index(row,0);
                    model_search->setData(index, item->id);

                    index = model_search->index(row,1);
                    model_search->setData(index, item->name);

                    index = model_search->index(row,2);
                    model_search->setData(index, item->state);

                    index = model_search->index(row,3);
                    model_search->setData(index, item->city);

                    index = model_search->index(row,4);
                    model_search->setData(index, item->address);

                    ++row;
                }
                /// printing table
                ui->tableView->setModel(model_search);
            }
        }


    }else{
        QMessageBox::warning(this, "Argument", "Wrong number of parameters");
    }
}


void Search::on_pushButton_3_clicked()
{
    /// declaring table size + headers
    model_search = new QStandardItemModel(0, 5, this);
    model_search->setHeaderData(0, Qt::Horizontal, "ID");
    model_search->setHeaderData(1, Qt::Horizontal, "Name");
    model_search->setHeaderData(2, Qt::Horizontal, "State");
    model_search->setHeaderData(3, Qt::Horizontal, "City");
    model_search->setHeaderData(4, Qt::Horizontal, "Address");

    /// printing table
    ui->tableView->setModel(model_search);
}

