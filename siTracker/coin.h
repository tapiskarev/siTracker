#ifndef COIN_H
#define COIN_H

#include <QString>
#include <QVector>
#include <QSet>



// Structure Purchase
struct Purchase{

    double price;       // purchased price
    double amount;      // received amount (coin)
    double total;       // expended money (USD)
    double fee;         // fees (coin)
    QString time;       // purchase time
    QString pair;       // transaction pair
    QString order_id;   // order id


    // reloaded == operator
    friend bool operator == (const Purchase &purchase1, const Purchase &purchase2){
        return (purchase1.price == purchase2.price) &&
                (purchase1.amount == purchase2.amount) &&
                (purchase1.total == purchase2.total) &&
                (purchase1.fee == purchase2.fee) &&
                (purchase1.time == purchase2.time) &&
                (purchase1.pair == purchase2.pair) &&
                (purchase1.order_id == purchase2.order_id);
    }
};


// Structure Sale
struct Sale{

    double price;       // sold price
    double amount;      // sold amount (coin)
    double total;       // received money (USD)
    double fee;         // fees (coin)
    QString time;       // sale time
    QString pair;       // transaction pair
    QString order_id;   // order id

    // reloaded == operator
    friend bool operator == (const Sale &sale1, const Sale &sale2){
        return (sale1.price == sale2.price) &&
                (sale1.amount == sale2.amount) &&
                (sale1.total == sale2.total) &&
                (sale1.fee == sale2.fee) &&
                (sale1.time == sale2.time) &&
                (sale1.pair == sale2.pair) && (sale1.order_id == sale2.order_id);
    }
};


// Class Coin
class Coin
{

public:
    // Coin History Info
    QString ticker;                     // coin ticker
    double amount;                      // coin amount
    double total;                       // invested money
    double averagePrice;                // coin average price
    QSet<QString> marketPlaces;         // marketplaces where trades
    QVector<Purchase> purchases;        // coin purchases
    QVector<Sale> sales;                // coin sales

    // Coin Current Info
    double currentPrice = 0;            // current price of a coin
    double currentTotal = 0;            // current tital of a coin
    double percentage = 0;              // difference in percentage


public:
    // Constructor + Desctructor
    Coin();
};

#endif // COIN_H
