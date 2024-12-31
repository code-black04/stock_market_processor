#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>
class Transaction
{
private:
    std::string orderID;
    char type; // 'B' for Buy, 'S' for Sell
    int quantity;
    double price;

public:
    Transaction(const std::string &id, char t, int qty, double pr);

    std::string getOrderID() const;
    char getType() const;
    int getQuantity() const;
    double getPrice() const;
};

#endif // TRANSACTION_H
