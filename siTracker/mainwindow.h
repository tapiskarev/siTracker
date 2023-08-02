#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMap>
#include <QStandardItemModel>
#include <fstream>
#include <QMessageBox>
#include <QTableView>

#include "coin.h"



// MainWindow Ui
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// MainWindow Class
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    // Constructor + Desctructor
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Methods
    void LoadData(QFile& file, QMap<QString, Coin>& map, QStandardItemModel& model, int tab);

    void UpdatePortfolioTable(QMap<QString, Coin>& map, QStandardItemModel& model, int tab);

    void ModelFill(QMap<QString, Coin>& map, QStandardItemModel& model, int tab);

    void UpdateInvestedMoney(QMap<QString, Coin>& map, QStandardItemModel& model, int tab);

    void SaveFile(std::string fileName, QMap<QString, Coin>& map, QStandardItemModel& model, int tab);

    void ClearFile(std::string fileName, double& investedMoney, double& currentMoney, QMap<QString, Coin>& map, QStandardItemModel& model, int tab);

    void Search(QMap<QString, Coin>& map, QStandardItemModel& model, int tab);

    void PurchaseSale(const QModelIndex& index, QMap<QString, Coin>& map, QStandardItemModel& model, int tab);

    void PriceUpdateFill(QMap<QString, Coin>& map, QString ticker, double current_price);

    void PriceUpdateUpdate(QMap<QString, Coin>& map, QStandardItemModel& model, int tab);

    void MapFill(QMap<QString, Coin>& map,
                 const QString &ticker,
                 const QString &order_id,
                 const QString &trade_type,
                 const QString &time,
                 const QString &pair,
                 const double &fee,
                 const double &price,
                 const double &amount,
                 const double &total);

    // Functions
    QStringList split(const QString& str);

    void TablePortfolioDeclare(QStandardItemModel& model);

    void TableOrderDeclare(QStandardItemModel& model);

    bool lessThan(const QModelIndex& left, const QModelIndex& right) const;


private slots:

    // File Buttons
    void on_actionAdd_Data_triggered();
    void on_actionSave_triggered();
    void on_actionClear_Storage_triggered();
    void on_actionQuit_triggered();
    void on_actionShow_Loaded_Files_triggered();

    // MW Buttons
    void on_tabWidget_currentChanged(int index);
    void on_pushButton_2_clicked();

    // ALL Buttons
    void on_pushButton_search_al_clicked();
    void on_tableView_portfolio_al_clicked(const QModelIndex &index);
    // SB Buttons
    void on_pushButton_search_sb_clicked();
    void on_tableView_portfolio_sb_clicked(const QModelIndex &index);

    // LS Buttons
    void on_pushButton_search_ls_clicked();
    void on_tableView_portfolio_ls_clicked(const QModelIndex &index);

    // SI Butons
    void on_pushButton_search_si_clicked();
    void on_tableView_portfolio_si_clicked(const QModelIndex &index);


private:

    // Ui
    Ui::MainWindow *ui;

    // MainWindow Private Data
    QString mw_newFileName = "";
    QSet<QString> mw_loadedFileNames;

    QMap<QString, Coin> mw_Map;
    QMap<QString, Coin> mw_Map_sb;
    QMap<QString, Coin> mw_Map_ls;
    QMap<QString, Coin> mw_Map_si;

    QString mw_pricesFileName =  "/Users/timpiskarev/Documents/Projects/Programming/QtCreator/Tracker App/data/prices.csv";
    QString mw_storageFileName =  "/Users/timpiskarev/Documents/Projects/Programming/QtCreator/Tracker App/data/storage.csv";

    QString mw_storageFileName_sb = "/Users/timpiskarev/Documents/Projects/Programming/QtCreator/Tracker App/data/storage_sb.csv";
    QString mw_storageFileName_ls = "/Users/timpiskarev/Documents/Projects/Programming/QtCreator/Tracker App/data/storage_ls.csv";
    QString mw_storageFileName_si = "/Users/timpiskarev/Documents/Projects/Programming/QtCreator/Tracker App/data/storage_si.csv";

    double mw_investedMoney = 0;
    double mw_currentMoney = 0;

    double mw_investedMoney_sb = 0;
    double mw_currentMoney_sb = 0;

    double mw_investedMoney_ls = 0;
    double mw_currentMoney_ls = 0;

    double mw_investedMoney_si = 0;
    double mw_currentMoney_si = 0;

    int mw_chosenTab = 0;


protected:

    // Childrens
    Coin* _coin;

    // Protected Data
    QStandardItemModel* _mw_portfolioModel;
    QStandardItemModel* _mw_portfolioModel_sb;
    QStandardItemModel* _mw_portfolioModel_ls;
    QStandardItemModel* _mw_portfolioModel_si;

};
#endif // MAINWINDOW_H
