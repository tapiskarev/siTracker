#include "mainwindow.h"
#include "./ui_mainwindow.h"



// Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /// UI setting up
    ui->setupUi(this);

    /// ALL model filling
    QFile file;
    file.setFileName(mw_storageFileName);

    int rows_num0 = mw_Map.size();
    _mw_portfolioModel = new QStandardItemModel(rows_num0, 9, this);
    TablePortfolioDeclare(*_mw_portfolioModel);

    LoadData(file, mw_Map, *_mw_portfolioModel, 0);

    /// SB model filling
    QFile file_sb;
    file_sb.setFileName(mw_storageFileName_sb);

    int rows_num1 = mw_Map_sb.size();
    _mw_portfolioModel_sb = new QStandardItemModel(rows_num1, 9, this);
    TablePortfolioDeclare(*_mw_portfolioModel_sb);

    LoadData(file_sb, mw_Map_sb, *_mw_portfolioModel_sb, 1);

    /// LS model filling
    QFile file_ls;
    file_ls.setFileName(mw_storageFileName_ls);

    int rows_num2 = mw_Map_ls.size();
    _mw_portfolioModel_ls = new QStandardItemModel(rows_num2, 9, this);
    TablePortfolioDeclare(*_mw_portfolioModel_ls);

    LoadData(file_ls, mw_Map_ls, *_mw_portfolioModel_ls, 2);

    /// SI model filling
    QFile file_si;
    file_si.setFileName(mw_storageFileName_si);

    int rows_num3 = mw_Map_si.size();
    _mw_portfolioModel_si = new QStandardItemModel(rows_num3, 9, this);
    TablePortfolioDeclare(*_mw_portfolioModel_si);

    LoadData(file_si, mw_Map_si, *_mw_portfolioModel_si, 3);
}


// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}


// Quiting App
void MainWindow::on_actionQuit_triggered()
{
    MainWindow::close();
}


// Saving Chosen Tab Number
void MainWindow::on_tabWidget_currentChanged(int index)
{
    // saving changed index
    mw_chosenTab = index;
}


// Splitting String
QStringList MainWindow::split(const QString& str)
{
    /// declaring item string to store the current "word" upto del + returning vector with items
    QString item;
    QStringList lineList;
    /// declaring index of quoted line
    int quoted_line_index = 0;

    for(QChar i : str){


        /// Char is NOT , or "
        if(i != ',' and i != '"'){
            item += i;
        }
        /// Char is , or "
        else{
            /// Char is ,
            if (i == ','){

                if (quoted_line_index == 0){
                    lineList.push_back(item);
                    item = "";
                }else{
                    item += i;
                }
            }
            /// char is "
            else{
                /// opening quote
                if (item.isEmpty()){
                    item = "";
                    quoted_line_index = 1;
                }
                /// closing quote
                else{
                    quoted_line_index = 0;
                }
            }
        }
    }

    lineList.push_back(item);
    return lineList;
}


// Sorting Model Function
bool MainWindow::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
    QString stringA = _mw_portfolioModel->data(left).toString();
    QString stringB = _mw_portfolioModel->data(right).toString();

    return stringA < stringB;
}


// Opening File
void MainWindow::on_actionAdd_Data_triggered()
{

    /// Opening file
    QString fileName;
    fileName = QFileDialog::getOpenFileName(
                                this,                                                       // parent window (current main window)
                                tr("Open File"),                                            // caption
                                "/Users/timpiskarev/Documents/Projects/Trading/TradeHistory/GATE.IO",                 // init dir
                                tr("All Files (*.*);; Text Files (*.txt) ;; CSV (*.csv)")   // mask
                                );

    /// empty check
   if (fileName.isNull()){
       return;
   }

   /// declaring File
   QFile file;
   file.setFileName(fileName);

   /// saving file name
   mw_newFileName = fileName;
   mw_loadedFileNames.insert(fileName);

   /// filling new data (ALL)
   LoadData(file, mw_Map, *_mw_portfolioModel, 0);

   /// LS
   if (mw_chosenTab == 1)
   {
       /// filling new data (SB)
       LoadData(file, mw_Map_sb, *_mw_portfolioModel_sb, 1);
   }
   else if (mw_chosenTab == 2)
   {
       /// filling new data (LS)
       LoadData(file, mw_Map_ls, *_mw_portfolioModel_ls, 2);
   }
   else if (mw_chosenTab == 3)
   {
       /// filling new data (SI)
       LoadData(file, mw_Map_si, *_mw_portfolioModel_si, 3);
   }
}


// Saving File Slot
void MainWindow::on_actionSave_triggered()
{    
    /// ALL saving
    MainWindow::SaveFile(mw_storageFileName.toStdString(), mw_Map, *_mw_portfolioModel, 0);

    /// SB saving
    MainWindow::SaveFile(mw_storageFileName_sb.toStdString(), mw_Map_sb, *_mw_portfolioModel_sb, 1);

    /// LS saving
    MainWindow::SaveFile(mw_storageFileName_ls.toStdString(), mw_Map_ls, *_mw_portfolioModel_ls, 2);

    /// SI saving
    MainWindow::SaveFile(mw_storageFileName_si.toStdString(), mw_Map_si, *_mw_portfolioModel_si, 3);
}


// Saving file Method
void MainWindow::SaveFile(std::string fileName, QMap<QString, Coin>& map, QStandardItemModel& model, int tab)
{
    /// declaring output stream file
    std::ofstream fileOut;
    fileOut.open(fileName);

    /// filling headers to the saving file
    fileOut << "No,Order id,Time,Trade type,Pair,Price,Amount,Fee,Total" << '\n';
    int no = 1;

    /// filling file with main map
    for (Coin coin : map)
    {
        for (Purchase purchase : coin.purchases)
        {
            /// outputting each variable
            fileOut << no++ << ',';
            fileOut << purchase.order_id.toStdString() << ',';
            fileOut << purchase.time.toStdString() << ',';
            fileOut << "Buy" << ',';
            fileOut << purchase.pair.toStdString() << ',';
            fileOut << std::to_string(purchase.price) << "000USDT" << ',';
            fileOut << std::to_string(purchase.amount) << "000" << coin.ticker.toStdString() << ',';
            fileOut << std::to_string(purchase.fee) << "000" << coin.ticker.toStdString() << ',';
            fileOut << std::to_string(purchase.total) << "000USDT" << '\n';
        }

        for (Sale sale : coin.sales)
        {
            /// outputting each variable
            fileOut << no++ << ',';
            fileOut << sale.order_id.toStdString() << ',';
            fileOut << sale.time.toStdString() << ',';
            fileOut << "Sell" << ',';
            fileOut << sale.pair.toStdString() << ',';
            fileOut << std::to_string(sale.price) << "000USDT" << ',';
            fileOut << std::to_string(sale.amount) << "000" << coin.ticker.toStdString() << ',';
            fileOut << std::to_string(sale.fee) << "000" << coin.ticker.toStdString() << ',';
            fileOut << std::to_string(sale.total) << "000USDT" << '\n';
        }
    }

    /// closing output file
    fileOut.close();
}


// Clearing Storage Slot
void MainWindow::on_actionClear_Storage_triggered()
{
    /// clearing ALL tab
    MainWindow::ClearFile(mw_storageFileName.toStdString(), mw_investedMoney, mw_currentMoney, mw_Map, *_mw_portfolioModel, 0);

    /// clearing SB tab
    MainWindow::ClearFile(mw_storageFileName_sb.toStdString(), mw_investedMoney_sb, mw_currentMoney_sb, mw_Map_sb, *_mw_portfolioModel_sb, 1);

    /// clearing LS tab
    MainWindow::ClearFile(mw_storageFileName_ls.toStdString(), mw_investedMoney_ls, mw_currentMoney_ls, mw_Map_ls, *_mw_portfolioModel_ls, 2);

    /// clearing SI tab
    MainWindow::ClearFile(mw_storageFileName_si.toStdString(), mw_investedMoney_si, mw_currentMoney_si, mw_Map_si, *_mw_portfolioModel_si, 3);
}


// Clear Method
void MainWindow::ClearFile(std::string fileName, double& investedMoney, double& currentMoney, QMap<QString, Coin>& map, QStandardItemModel& model, int tab)
{
    /// declaring output stream file
    std::ofstream fileOut;
    fileOut.open(fileName);

    /// filling headers to the saving file
    fileOut << "No,Order id,Time,Trade type,Pair,Price,Amount,Fee,Total" << '\n';

    /// closing output file
    fileOut.close();

    /// map clearing
    map.clear();

    /// invested money clear
    investedMoney = 0;

    /// current money clear
    currentMoney = 0;

    /// loaded filenames clear
    mw_loadedFileNames.clear();

    /// updating 0 invested money
    MainWindow::UpdateInvestedMoney(map, model, tab);

    /// updating 0 portfolio table
    MainWindow::UpdatePortfolioTable(map, model, tab);

    /// empty models print
    QStandardItemModel* emptyModel = new QStandardItemModel(0, 6, this);
    TableOrderDeclare(*emptyModel);

    ui->tableView_orders_al->setModel(emptyModel);
    ui->tableView_orders_sb->setModel(emptyModel);
    ui->tableView_orders_ls->setModel(emptyModel);
    ui->tableView_orders_si->setModel(emptyModel);

    ui->tableView_sales_al->setModel(emptyModel);
    ui->tableView_sales_sb->setModel(emptyModel);
    ui->tableView_sales_ls->setModel(emptyModel);
    ui->tableView_sales_si->setModel(emptyModel);

    /// updating orders labels
    ui->label_orders_al->setText("ORDERS");
    ui->label_orders_sb->setText("ORDERS");
    ui->label_orders_ls->setText("ORDERS");
    ui->label_orders_si->setText("ORDERS");
}


// Map Filling
void MainWindow::MapFill(QMap<QString, Coin>& map,
                         const QString &ticker, const QString &order_id, const QString &trade_type,
                         const QString &time, const QString &pair, const double &fee,
                         const double &price, const double &amount, const double &total)
{
    /// filling coin data: Ticker, Markets
    map[ticker].ticker = ticker;
    QString market = "Gate.io";
    map[ticker].marketPlaces.insert(market);

    /// next steps depend on the type of transaction: buy or sell
    if (trade_type == "Buy")
    {
        /// increasing Amount and Total values
        map[ticker].amount += (amount - fee);
        map[ticker].total += total;

        /// filling vector purchases
        map[ticker].purchases.push_back({price, amount, total, fee, time, pair, order_id});

    }
    else if (trade_type == "Sell")
    {
        /// decreasing Amount and Total values
        map[ticker].amount -= amount;
        map[ticker].total -= (total + fee);

        /// filling vector sales
        map[ticker].sales.push_back({price, amount, total, fee, time, pair, order_id});
    }

    // filling averagePrice
    map[ticker].averagePrice = map[ticker].total / map[ticker].amount;
}


// Loading New Data
void MainWindow::LoadData(QFile &file, QMap<QString, Coin>& map, QStandardItemModel& model, int tab)
{
    /// mistakes check
    if (!file.open(QIODevice::ReadWrite))
    {
        throw QString("File cannot be opened!");
    }

    /// reading file
    for (size_t j = 0; !file.atEnd(); j++)
    {

        /// making an info line
        QString line(QByteArray(file.readLine()));

        /// headers check
        if (j != 0)
        {
            /// line splitting
            QStringList splittedLine;
            splittedLine = MainWindow::split(line);

            /// declaring Coin ticker
            QString Ticker;

            /// declaring Order data (in string)
            QString str_No, str_Order_id, str_Time, str_Trade_type,
                    str_Pair, str_Price, str_Amount, str_Fee, str_Total, str_Maker_Taker;

            /// declaring Order data (needed)
            QString No, Order_id, Time, Trade_type, Pair;
            double Price, Amount, Fee, Total;

            /// Order data (in string) filling
            str_No = splittedLine[0];
            str_Order_id = splittedLine[1];
            str_Time = splittedLine[2];
            str_Trade_type = splittedLine[3];
            str_Maker_Taker = splittedLine[4];
            str_Pair = splittedLine[4];
            str_Price = splittedLine[5];
            str_Amount = splittedLine[6];
            str_Fee = splittedLine[7];
            str_Total = splittedLine[8];

            /// getting the ticker of a coin from Pair
            for(QChar x : str_Pair){
                if (x != '/'){
                    Ticker+=x;
                }
                else{break;}
            }

            /// cleaning Price from "USDT"
            QString price_cleaned;
            for(QChar x : str_Price){
                if (x != 'U'){
                    price_cleaned+=x;
                }
                else{break;}
            }

            /// cleaning Amount from Ticker
            QString amount_cleaned;
            QChar ch1 = Ticker[0];
            QChar ch2 = Ticker[1];
            int ind = 0;

            for(QChar x : str_Amount){
                if ((x == ch1)&(str_Amount[ind + 1] == ch2)){
                    ind = 0;
                    break;
                }
                else{
                    amount_cleaned+=x;
                    ++ind;
                }
            }

            /// cleaning Fee from Ticker
            QString fee_cleaned;

            /// buy check
            if (str_Trade_type == "Buy")
                for(QChar x : str_Fee){
                    if ((x == ch1)&(str_Fee[ind + 1] == ch2)){
                        break;
                    }
                    else{
                        fee_cleaned+=x;
                        ++ind;
                    }
                }
            /// sell check
            else
                for(QChar x : str_Fee){
                    if (x != 'U'){
                        fee_cleaned+=x;
                    }
                    else{break;}
                }

            /// cleaning Total from "USDT"
            QString total_cleaned;
            for(QChar x : str_Total){
                if (x != 'U'){
                    total_cleaned+=x;
                }
                else{break;}
            }

            /// converting string to needed types
            No = str_No;
            Order_id = str_Order_id;
            Time = str_Time;
            Trade_type = str_Trade_type;
            Pair = str_Pair;
            Price = price_cleaned.toDouble();
            Amount = amount_cleaned.toDouble();
            Fee = fee_cleaned.toDouble();
            Total = total_cleaned.toDouble();

            /// checking if map already contains this purchase/sell
            /// coin is not in map yet
            if (!map.contains(Ticker))
            {
                MainWindow::MapFill(map, Ticker, Order_id, Trade_type, Time, Pair,
                                    Fee, Price, Amount, Total);
            }
            /// coin is already in the map and this purchase/sell is new
            else
            {
                /// uniquiness check for purchase
                if (Trade_type == "Buy")
                {
                    /// unique check
                    if (!map[Ticker].purchases.contains({Price, Amount, Total, Fee, Time, Pair, Order_id}))
                    {
                        MainWindow::MapFill(map, Ticker, Order_id, Trade_type, Time, Pair,
                                            Fee, Price, Amount, Total);
                    }
                }
                /// uniquiness check for sell
                else
                {
                    /// unique check
                    if (!map[Ticker].sales.contains({Price, Amount, Total, Fee, Time, Pair, Order_id}))
                    {
                        MainWindow::MapFill(map, Ticker, Order_id, Trade_type, Time, Pair,
                                            Fee, Price, Amount, Total);
                    }
                }
            }
        }
    }


    /// updating table
    MainWindow::UpdatePortfolioTable(map, model, tab);

    /// updating all invested money label
    MainWindow::UpdateInvestedMoney(map, model, tab);

    /// printing the name of the last added file
    QString lastFileName = "last loaded file: " + mw_newFileName;
    ui->statusbar->showMessage(lastFileName, 0);

    /// file closing
    file.close();
}


// Updating Table
void MainWindow::UpdatePortfolioTable(QMap<QString, Coin>& map, QStandardItemModel& model, int tab)
{
    /// model filling
    /// declaring table size + headers
    int rows_num = map.size();
    model.setRowCount(rows_num);

    /// filling table;
    MainWindow::ModelFill(map, model, tab);

    /// ALL tab
    if (tab == 0)
    {
        /// printing table
        ui->tableView_portfolio_al->setModel(&model);

        /// sorting able
        ui->tableView_portfolio_al->setSortingEnabled(true);
        ui->tableView_portfolio_al->sortByColumn(0, Qt::SortOrder::AscendingOrder);
    }
    /// SB tab
    else if (tab == 1)
    {
        /// printing table
        ui->tableView_portfolio_sb->setModel(&model);

        /// sorting able
        ui->tableView_portfolio_sb->setSortingEnabled(true);
        ui->tableView_portfolio_sb->sortByColumn(0, Qt::SortOrder::AscendingOrder);
    }
    /// LS tab
    else if (tab == 2)
    {
        /// printing table
        ui->tableView_portfolio_ls->setModel(&model);

        /// sorting able
        ui->tableView_portfolio_ls->setSortingEnabled(true);
        ui->tableView_portfolio_ls->sortByColumn(0, Qt::SortOrder::AscendingOrder);
    }
    /// SI tab
    else if (tab == 3)
    {
        /// printing table
        ui->tableView_portfolio_si->setModel(&model);

        /// sorting able
        ui->tableView_portfolio_si->setSortingEnabled(true);
        ui->tableView_portfolio_si->sortByColumn(0, Qt::SortOrder::AscendingOrder);
    }
}


// Model Filling
void MainWindow::ModelFill(QMap<QString, Coin>& map, QStandardItemModel& model, int tab)
{
    /// filling table;
    QModelIndex index;
    int row = 0;

    for (Coin item : map){

        index = model.index(row,0);
        model.setData(index, item.ticker);

        index = model.index(row,1);
        model.setData(index, item.amount);

        index = model.index(row,2);
        model.setData(index, item.total);

        index = model.index(row,3);
        model.setData(index, item.currentTotal);

        index = model.index(row,4);
        model.setData(index, item.averagePrice);

        index = model.index(row,5);
        model.setData(index, item.currentPrice);

        index = model.index(row,6);
        model.setData(index, std::round(item.percentage * 100.0));

        index = model.index(row,7);
        model.setData(index, item.purchases.size());

        index = model.index(row,8);
        model.setData(index, item.sales.size());

        ++row;
    }
}


// Updating Money Invested
void MainWindow::UpdateInvestedMoney(QMap<QString, Coin>& map, QStandardItemModel& model, int tab)
{
    /// ALL tab
    if (tab == 0)
    {
        /// invested/current money to zero
        mw_investedMoney = 0;
        mw_currentMoney = 0;

        /// counting all totals of each coin
        for(Coin coin : map){
            mw_investedMoney += coin.total;
            mw_currentMoney += coin.currentTotal;
        }

        /// printing invested money + current money + percentage
        ui->label_investedMoney_al->setText("Invested money:   $" + QString::number(mw_investedMoney));
        ui->label_currentMoney_al->setText("Current money:    $" + QString::number(mw_currentMoney));
        ui->label_percentage_al->setText("Percentage:          " + QString::number(std::round(((mw_currentMoney - mw_investedMoney)
                                                                                    / mw_investedMoney) * 100.0)) + "%");
    }
    /// SB tab
    else if (tab == 1)
    {
        /// invested/current money to zero
        mw_investedMoney_sb = 0;
        mw_currentMoney_sb= 0;

        /// counting all totals of each coin
        for(Coin coin : map){
            mw_investedMoney_sb += coin.total;
            mw_currentMoney_sb += coin.currentTotal;
        }

        /// printing invested money + current money + percentage
        ui->label_investedMoney_sb->setText("Invested money:   $" + QString::number(mw_investedMoney_sb));
        ui->label_currentMoney_sb->setText("Current money:    $" + QString::number(mw_currentMoney_sb));
        ui->label_percentage_sb->setText("Percentage:          " + QString::number(std::round(((mw_currentMoney_sb - mw_investedMoney_sb)
                                                                                    / mw_investedMoney_sb) * 100.0)) + "%");
    }
    /// LS tab
    else if (tab == 2)
    {
        /// invested/current money to zero
        mw_investedMoney_ls = 0;
        mw_currentMoney_ls= 0;

        /// counting all totals of each coin
        for(Coin coin : map){
            mw_investedMoney_ls += coin.total;
            mw_currentMoney_ls += coin.currentTotal;
        }

        /// printing invested money + current money + percentage
        ui->label_investedMoney_ls->setText("Invested money:   $" + QString::number(mw_investedMoney_ls));
        ui->label_currentMoney_ls->setText("Current money:    $" + QString::number(mw_currentMoney_ls));
        ui->label_percentage_ls->setText("Percentage:          " + QString::number(std::round(((mw_currentMoney_ls - mw_investedMoney_ls)
                                                                                    / mw_investedMoney_ls) * 100.0)) + "%");
    }
    /// SI tab
    else if (tab == 3)
    {
        /// invested/current money to zero
        mw_investedMoney_si = 0;
        mw_currentMoney_si= 0;

        /// counting all totals of each coin
        for(Coin coin : map){
            mw_investedMoney_si += coin.total;
            mw_currentMoney_si += coin.currentTotal;
        }

        /// printing invested money + current money + percentage
        ui->label_investedMoney_si->setText("Invested money:   $" + QString::number(mw_investedMoney_si));
        ui->label_currentMoney_si->setText("Current money:    $" + QString::number(mw_currentMoney_si));
        ui->label_percentage_si->setText("Percentage:          " + QString::number(std::round(((mw_currentMoney_si - mw_investedMoney_si)
                                                                                    / mw_investedMoney_si) * 100.0)) + "%");
    }
}


// Declaring Portfolio Table Headers
void MainWindow::TablePortfolioDeclare(QStandardItemModel& model)
{
    model.setHeaderData(0, Qt::Horizontal, "Ticker");
    model.setHeaderData(1, Qt::Horizontal, "Amount");
    model.setHeaderData(2, Qt::Horizontal, "Total");
    model.setHeaderData(3, Qt::Horizontal, "Current Total");
    model.setHeaderData(4, Qt::Horizontal, "Average Price");
    model.setHeaderData(5, Qt::Horizontal, "Current Price");
    model.setHeaderData(6, Qt::Horizontal, "Percentage (%)");
    model.setHeaderData(7, Qt::Horizontal, "Purchases Number");
    model.setHeaderData(8, Qt::Horizontal, "Sales Number");
}


// Declaring Order Table Headers
void MainWindow::TableOrderDeclare(QStandardItemModel& model)
{
    model.setHeaderData(0, Qt::Horizontal, "Side");
    model.setHeaderData(1, Qt::Horizontal, "Time");
    model.setHeaderData(2, Qt::Horizontal, "Price");
    model.setHeaderData(3, Qt::Horizontal, "Amount");
    model.setHeaderData(4, Qt::Horizontal, "Total");
    model.setHeaderData(5, Qt::Horizontal, "Order ID");
}


// Purchases/Sales Slot (ALL)
void MainWindow::on_tableView_portfolio_al_clicked(const QModelIndex &index)
{
    /// p/s for ALL
    MainWindow::PurchaseSale(index, mw_Map, *_mw_portfolioModel, 0);
}


// Purchases/Sales Slot (SB)
void MainWindow::on_tableView_portfolio_sb_clicked(const QModelIndex &index)
{
    /// p/s for LS
    MainWindow::PurchaseSale(index, mw_Map_sb, *_mw_portfolioModel_sb, 1);
}


// Purchases/Sales Slot (LS)
void MainWindow::on_tableView_portfolio_ls_clicked(const QModelIndex& index)
{
    /// p/s for LS
    MainWindow::PurchaseSale(index, mw_Map_ls, *_mw_portfolioModel_ls, 2);
}


// Purchases/Sales Slot (SI)
void MainWindow::on_tableView_portfolio_si_clicked(const QModelIndex &index)
{
    /// p/s for LS
    MainWindow::PurchaseSale(index, mw_Map_si, *_mw_portfolioModel_si, 3);
}


// Purchases/Sales Method
void MainWindow::PurchaseSale(const QModelIndex& index, QMap<QString, Coin>& map, QStandardItemModel& model, int tab)
{

    /// taking row + column of selected item
    int rowPortfolio = index.row();
    int columnPortfolio = index.column();

    /// ticker getting
    QString ticker;
    ticker = model.item(rowPortfolio, 0)->text();

    /// declaring purchases model
    QStandardItemModel* model_purchases;
    model_purchases = new QStandardItemModel(map[ticker].purchases.size(), 6, this);
    TableOrderDeclare(*model_purchases);

    /// declaring sales model
    QStandardItemModel* model_sales;
    model_sales = new QStandardItemModel(map[ticker].sales.size(), 6, this);
    TableOrderDeclare(*model_sales);

    /// indeces declaring
    QModelIndex indexPurchases;
    QModelIndex indexSales;
    int rowPurchases = 0;
    int rowSales = 0;

    /// purchases
    for(Purchase purchase : map[ticker].purchases)
    {
        indexPurchases = model_purchases->index(rowPurchases,0);
        model_purchases->setData(indexPurchases, "Buy");

        indexPurchases = model_purchases->index(rowPurchases,1);
        model_purchases->setData(indexPurchases, purchase.time);

        indexPurchases = model_purchases->index(rowPurchases,2);
        model_purchases->setData(indexPurchases, purchase.price);

        indexPurchases = model_purchases->index(rowPurchases,3);
        model_purchases->setData(indexPurchases, purchase.amount);

        indexPurchases = model_purchases->index(rowPurchases,4);
        model_purchases->setData(indexPurchases, purchase.total);

        indexPurchases = model_purchases->index(rowPurchases,5);
        model_purchases->setData(indexPurchases, purchase.order_id);

        ++rowPurchases;
    }

    /// sales
    for(Sale sale : map[ticker].sales)
    {
        indexSales = model_sales->index(rowSales,0);
        model_sales->setData(indexSales, "Sell");

        indexSales = model_sales->index(rowSales,1);
        model_sales->setData(indexSales, sale.time);

        indexSales = model_sales->index(rowSales,2);
        model_sales->setData(indexSales, sale.price);

        indexSales = model_sales->index(rowSales,3);
        model_sales->setData(indexSales, sale.amount);

        indexSales = model_sales->index(rowSales,4);
        model_sales->setData(indexSales, sale.total);

        indexSales = model_sales->index(rowSales,5);
        model_sales->setData(indexSales, sale.order_id);

        ++rowSales;
    }

    /// ALL
    if (tab == 0)
    {
        /// printing ticker
        ui->label_orders_al->setText("ORDERS:   " + ticker);

        /// printing purchases table
        ui->tableView_orders_al->setModel(model_purchases);

        /// printing sales table
        ui->tableView_sales_al->setModel(model_sales);

        /// sorting able
        ui->tableView_orders_al->setSortingEnabled(true);
        ui->tableView_orders_al->sortByColumn(0, Qt::SortOrder::AscendingOrder);

        ui->tableView_sales_al->setSortingEnabled(true);
        ui->tableView_sales_al->sortByColumn(0, Qt::SortOrder::AscendingOrder);
    }
    /// SB
    else if (tab == 1)
    {
        /// printing ticker
        ui->label_orders_sb->setText("ORDERS:   " + ticker);

        /// printing table
        ui->tableView_orders_sb->setModel(model_purchases);

        /// printing sales table
        ui->tableView_sales_sb->setModel(model_sales);

        /// sorting able
        ui->tableView_orders_sb->setSortingEnabled(true);
        ui->tableView_orders_sb->sortByColumn(0, Qt::SortOrder::AscendingOrder);

        ui->tableView_sales_sb->setSortingEnabled(true);
        ui->tableView_sales_sb->sortByColumn(0, Qt::SortOrder::AscendingOrder);
    }
    /// LS
    else if (tab == 2)
    {
        /// printing ticker
        ui->label_orders_ls->setText("ORDERS:   " + ticker);

        /// printing table
        ui->tableView_orders_ls->setModel(model_purchases);

        /// printing sales table
        ui->tableView_sales_ls->setModel(model_sales);

        /// sorting able
        ui->tableView_orders_ls->setSortingEnabled(true);
        ui->tableView_orders_ls->sortByColumn(0, Qt::SortOrder::AscendingOrder);

        ui->tableView_sales_ls->setSortingEnabled(true);
        ui->tableView_sales_ls->sortByColumn(0, Qt::SortOrder::AscendingOrder);
    }
    /// SI
    else if (tab == 3)
    {
        /// printing ticker
        ui->label_orders_si->setText("ORDERS:   " + ticker);

        /// printing table
        ui->tableView_orders_si->setModel(model_purchases);

        /// printing sales table
        ui->tableView_sales_si->setModel(model_sales);

        /// sorting able
        ui->tableView_orders_si->setSortingEnabled(true);
        ui->tableView_orders_si->sortByColumn(0, Qt::SortOrder::AscendingOrder);

        ui->tableView_sales_si->setSortingEnabled(true);
        ui->tableView_sales_si->sortByColumn(0, Qt::SortOrder::AscendingOrder);
    }

}


// Showing Loaded FileNames
void MainWindow::on_actionShow_Loaded_Files_triggered()
{
    /// making a string with all loaded filenames
    QString allFilesNames;

    /// filling all filenames
    for(QString fileName : mw_loadedFileNames)
    {
        allFilesNames = allFilesNames + '\n' + '\n' + fileName;
    }

    /// adding the number of loaded files
    QString information = QString::number(mw_loadedFileNames.size()) + " Loaded Files:" + allFilesNames;

    /// printing filenames
    QMessageBox::information(this, "Loaded Files", information);
}


// Search Slot (ALL)
void MainWindow::on_pushButton_search_al_clicked()
{
    /// ALL searcing
    MainWindow::Search(mw_Map, *_mw_portfolioModel, 0);
}

// Search Slot (SB)
void MainWindow::on_pushButton_search_sb_clicked()
{
    /// SB searcing
    MainWindow::Search(mw_Map_sb, *_mw_portfolioModel_sb, 1);
}

// Search Slot (LS)
void MainWindow::on_pushButton_search_ls_clicked()
{
    /// LS searcing
    MainWindow::Search(mw_Map_ls, *_mw_portfolioModel_ls, 2);
}


// Search Slot (SI)
void MainWindow::on_pushButton_search_si_clicked()
{
    /// SI searcing
    MainWindow::Search(mw_Map_si, *_mw_portfolioModel_si, 3);
}


// Search Method
void MainWindow::Search(QMap<QString, Coin>& map, QStandardItemModel& model, int tab)
{
    /// declaring variables
    QString search;
    QMap<QString, Coin> searchMap;

    /// inputting searching info
    if (tab == 0)
    {
        search = ui->lineEdit_search_al->text();
    }
    else if (tab == 1)
    {
        search = ui->lineEdit_search_sb->text();
    }
    else if (tab == 2)
    {
        search = ui->lineEdit_search_ls->text();
    }
    else if (tab == 3)
    {
        search = ui->lineEdit_search_si->text();
    }

    /// searching coin
    for (auto coin : map)
    {
        // search string cointain check
        if (coin.ticker.contains(search))
        {
            // putting searched coin in new map
            searchMap[coin.ticker] = coin;
        }
    }

    /// clearing model
    model.clear();

    /// defining cleared model
    model.setRowCount(searchMap.size());
    model.setColumnCount(9);
    MainWindow::TablePortfolioDeclare(model);

    /// filling table;
    MainWindow::ModelFill(searchMap, model, tab);

    if (tab == 0)
    {
        /// printing table
        ui->tableView_portfolio_al->setModel(&model);

        /// sorting able
        ui->tableView_portfolio_al->setSortingEnabled(true);
        ui->tableView_portfolio_al->sortByColumn(0, Qt::SortOrder::AscendingOrder);
    }
    else if (tab == 1)
    {
        /// printing table
        ui->tableView_portfolio_sb->setModel(&model);

        /// sorting able
        ui->tableView_portfolio_sb->setSortingEnabled(true);
        ui->tableView_portfolio_sb->sortByColumn(0, Qt::SortOrder::AscendingOrder);
    }
    else if (tab == 2)
    {
        /// printing table
        ui->tableView_portfolio_ls->setModel(&model);

        /// sorting able
        ui->tableView_portfolio_ls->setSortingEnabled(true);
        ui->tableView_portfolio_ls->sortByColumn(0, Qt::SortOrder::AscendingOrder);
    }
    else if (tab == 3)
    {
        /// printing table
        ui->tableView_portfolio_si->setModel(&model);

        /// sorting able
        ui->tableView_portfolio_si->setSortingEnabled(true);
        ui->tableView_portfolio_si->sortByColumn(0, Qt::SortOrder::AscendingOrder);
    }
}


// Prices Update Slot
void MainWindow::on_pushButton_2_clicked()
{
    /// reading prices.csv file
    QFile file;
    file.setFileName(mw_pricesFileName);

    /// mistakes check
    if (!file.open(QIODevice::ReadWrite))
    {
        throw QString("File cannot be opened!");
    }

    /// making tickers line
    QString line1(QByteArray(file.readLine()));

    /// making prices line
    QString line2(QByteArray(file.readLine()));

    /// lines splitting
    QStringList splittedLine1 = MainWindow::split(line1);
    QStringList splittedLine2 = MainWindow::split(line2);

    /// map filling with current prices
    for (int i = 0; i < splittedLine1.size(); ++i)
    {
        /// last ticker in line
        if (i == splittedLine1.size() - 1)
        {
            /// declaring new last ticker QString
            QString ticker;

            /// deleting '\ n'
            for (char ch : splittedLine1[i].toStdString())
            {
                if ((65 <= ch && ch <= 90) | (97 <= ch && ch <= 122)){ticker += ch;}
                else{break;}
            }

            /// prices filling (ALL)
            MainWindow::PriceUpdateFill(mw_Map, ticker, splittedLine2[i].toDouble());

            /// prices filling (SB)
            MainWindow::PriceUpdateFill(mw_Map_sb, ticker, splittedLine2[i].toDouble());

            /// prices filling (LS)
            MainWindow::PriceUpdateFill(mw_Map_ls, ticker, splittedLine2[i].toDouble());

            /// prices filling (SI)
            MainWindow::PriceUpdateFill(mw_Map_si, ticker, splittedLine2[i].toDouble());
        }
        /// not last ticker in line
        else
        {
            /// prices filling (ALL)
            MainWindow::PriceUpdateFill(mw_Map, splittedLine1[i], splittedLine2[i].toDouble());

            /// prices filling (SB)
            MainWindow::PriceUpdateFill(mw_Map_sb, splittedLine1[i], splittedLine2[i].toDouble());

            /// prices filling (LS)
            MainWindow::PriceUpdateFill(mw_Map_ls, splittedLine1[i], splittedLine2[i].toDouble());

            /// prices filling (SI)
            MainWindow::PriceUpdateFill(mw_Map_si, splittedLine1[i], splittedLine2[i].toDouble());
        }
    }

    /// updating table (ALL)
    MainWindow::PriceUpdateUpdate(mw_Map, *_mw_portfolioModel, 0);

    /// updating table (SB)
    MainWindow::PriceUpdateUpdate(mw_Map_sb, *_mw_portfolioModel_sb, 1);

    /// updating table (LS)
    MainWindow::PriceUpdateUpdate(mw_Map_ls, *_mw_portfolioModel_ls, 2);

    /// updating table (SI)
    MainWindow::PriceUpdateUpdate(mw_Map_si, *_mw_portfolioModel_si, 3);
}


// Prices Update Fill Method
void MainWindow::PriceUpdateFill(QMap<QString, Coin>& map, QString ticker, double current_price)
{
    /// coin in map check
    if (map.contains(ticker))
    {
        /// filling coin's current price
        map[ticker].currentPrice = current_price;

        /// filling coin's current current total
        map[ticker].currentTotal = map[ticker].currentPrice * map[ticker].amount;

        /// filling coin's percentage difference
        map[ticker].percentage = (map[ticker].currentTotal - map[ticker].total) / map[ticker].total;
    }
}


// Prices Update Update Method
void MainWindow::PriceUpdateUpdate(QMap<QString, Coin>& map, QStandardItemModel& model, int tab)
{
    /// updating table
    MainWindow::UpdatePortfolioTable(map, model, tab);

    /// updating all invested money label
    MainWindow::UpdateInvestedMoney(map, model, tab);
}

































































































