#include "edit.h"
#include "ui_edit.h"



Edit::Edit(QWidget *parent)
    : QDialog(parent)
    , _hospitals(new Hospitals(this))
    , ui(new Ui::Edit)
{
    ui->setupUi(this);
}

Edit::~Edit()
{
    delete ui;
}

// Saving FileName
void Edit::SaveFileName(QString filename){
    fileNameSaved = filename;
}


// Closing Widget
void Edit::on_pushButton_clicked()
{
    QWidget::close();
}


void Edit::on_button_add_clicked()
{
    if(_hospitals->openFile(Edit::fileNameSaved))
    {

        QVector<std::string> re_storage;

        std::string fileReName = fileNameSaved.toStdString();


        std::ifstream fileIn;
        fileIn.open(fileReName);


        while(fileIn.good()){
            std::string line;
            std::getline(fileIn, line, '\n');
            re_storage.append(line);
        }

        std::ofstream fileOut;
        fileOut.open(fileReName);

        int num_csv = re_storage.size();
        int i = 0;

        for(std::string str : re_storage){

            if (i != (num_csv - 1)){
                fileOut << str << '\n';
            } else{
                fileOut << str;
            }
            ++i;
        }
        fileOut << '\n';

        std::string new_name = (ui->add_name->text()).toStdString();
        std::string new_id = (ui->add_id->text()).toStdString();
        std::string new_address = (ui->add_address->text()).toStdString();
        std::string new_city = (ui->add_city->text()).toStdString();
        std::string new_state = (ui->add_state->text()).toStdString();




        fileOut << "NOT AVAILABLE" << ',' << "NOT AVAILABLE" << ',' << new_id << ',' << "NOT AVAILABLE" << ',' << new_name << ',' << new_address << ',' << new_city << ',' << new_state << ',';

        for(int j = 0; j!=26; ++j){
            if (j != 25){
                fileOut << "NOT AVAILABLE" << ',';
            } else{
                fileOut << "NOT AVAILABLE";
            }
        }
    }
    QMessageBox::information(this, "Information", "Item was successfully added");
}


void Edit::on_button_delete_clicked()
{
    if(_hospitals->openFile(Edit::fileNameSaved))
    {

        QVector<std::string> re_storage;

        std::string fileReName = fileNameSaved.toStdString();


        std::ifstream fileIn;
        fileIn.open(fileReName);


        std::string delete_id = (ui->delete_id->text()).toStdString();

        while(fileIn.good()){
            std::string line;
            std::getline(fileIn, line, '\n');



            if( !(line.find(delete_id) != std::string::npos)) {
                re_storage.append(line);
            }
        }

        std::ofstream fileOut;
        fileOut.open(fileReName);

        int num_csv = re_storage.size();
        int i = 0;

        for(std::string str : re_storage){

            if (i != (num_csv - 1)){
                fileOut << str << '\n';
            } else{
                fileOut << str;
            }
            ++i;
        }

    }
    QMessageBox::information(this, "Information", "Item was successfully deleted");
}


