#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTextStream>
#include <QStandardItemModel>
#include <QMessageBox>

#include "hospitals.h"
#include "showamount.h"
#include "search.h"
#include "edit.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString fileNameSt;

protected:

    Hospitals* _hospitals;

private slots:

    void on_actionOpen_triggered();
    void on_actionQuit_triggered();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    ShowAmount *win1;
    Search *win2;
    Edit *win3;
    QStandardItemModel *model_all;
};
#endif // MAINWINDOW_H
