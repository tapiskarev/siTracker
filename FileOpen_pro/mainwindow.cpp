#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _hospitals(new Hospitals(this))
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}



// Opening File + Showing Table
void MainWindow::on_actionOpen_triggered()
{
    /// Opening file
    QString fileName;
    fileName = QFileDialog::getOpenFileName(
                                this,                                                       // parent window (current main window)
                                tr("Open File"),                                            // caption
                                "C:/Education/HSE/2021-2022/Programming/C++/HomeWork/BigHW/MyHW/FileOpen_pro/FileOpen_pro/data/open",                                                         // init dir
                                tr("All Files (*.*);; Text Files (*.txt) ;; CSV (*.csv)")  // mask
                                );

     /// empty check
    if (fileName.isNull()){
        return;
    }

    /// saving file name
     fileNameSt = fileName;


    /// Showing table
    if(_hospitals->openFile(fileName))
    {
        /// declaring table size + headers
        int rows_num = _hospitals->getMapSize();
        model_all = new QStandardItemModel(rows_num, 5, this);
        model_all->setHeaderData(0, Qt::Horizontal, "ID");
        model_all->setHeaderData(1, Qt::Horizontal, "Name");
        model_all->setHeaderData(2, Qt::Horizontal, "State");
        model_all->setHeaderData(3, Qt::Horizontal, "City");
        model_all->setHeaderData(4, Qt::Horizontal, "Address");


        /// filling table
        QMap<QString, Clinic*> copyMapClinics = _hospitals->getMapClinicsData();
        QModelIndex index;
        int row = 0;

        for (Clinic * item : copyMapClinics){

            index = model_all->index(row,0);
            model_all->setData(index, item->id);

            index = model_all->index(row,1);
            model_all->setData(index, item->name);

            index = model_all->index(row,2);
            model_all->setData(index, item->state);

            index = model_all->index(row,3);
            model_all->setData(index, item->city);

            index = model_all->index(row,4);
            model_all->setData(index, item->address);

            ++row;
        }

        /// printing table
        ui->tableView->setModel(model_all);
    }

}


// Quiting
void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}



void MainWindow::on_pushButton_3_clicked()
{
    if(_hospitals->openFile(MainWindow::fileNameSt))
    {

        win1 = new ShowAmount(this);
        win1->show();
        win1->SaveFileName(MainWindow::fileNameSt);
    }
    else{
        QMessageBox::warning(this, "File", "File is not open");
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    if(_hospitals->openFile(MainWindow::fileNameSt))
    {
        win2 = new Search(this);
        win2->show();
        win2->SaveFileName(MainWindow::fileNameSt);
    }
    else{
        QMessageBox::warning(this, "File", "File is not open");
    }
}



void MainWindow::on_pushButton_clicked()
{
    if(_hospitals->openFile(MainWindow::fileNameSt))
    {
        win3 = new Edit(this);
        win3->show();
        win3->SaveFileName(MainWindow::fileNameSt);
    }
    else{
        QMessageBox::warning(this, "File", "File is not open");
    }
}




void MainWindow::on_pushButton_4_clicked()
{


    /// Showing table
    if(_hospitals->openFile(MainWindow::fileNameSt))
    {

        /// declaring table size + headers
        int rows_num = _hospitals->getMapSize();
        model_all = new QStandardItemModel(rows_num, 5, this);
        model_all->setHeaderData(0, Qt::Horizontal, "ID");
        model_all->setHeaderData(1, Qt::Horizontal, "Name");
        model_all->setHeaderData(2, Qt::Horizontal, "State");
        model_all->setHeaderData(3, Qt::Horizontal, "City");
        model_all->setHeaderData(4, Qt::Horizontal, "Address");


        /// filling table
        QMap<QString, Clinic*> copyMapClinics = _hospitals->getMapClinicsData();
        QModelIndex index;
        int row = 0;

        for (Clinic * item : copyMapClinics){

            index = model_all->index(row,0);
            model_all->setData(index, item->id);

            index = model_all->index(row,1);
            model_all->setData(index, item->name);

            index = model_all->index(row,2);
            model_all->setData(index, item->state);

            index = model_all->index(row,3);
            model_all->setData(index, item->city);

            index = model_all->index(row,4);
            model_all->setData(index, item->address);

            ++row;
        }

        /// printing table
        ui->tableView->setModel(model_all);

    }
    else{
        QMessageBox::warning(this, "File", "File is not open");
    }

}

