#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include "transaction.h"

class Order
{
private:
    std::string orderID;
    char type; // 'B' for Buy, 'S' for Sell
    int quantity;
    double price; // Default to -1 if no price is provided
    bool hasPrice;
    std::vector<Transaction<std::string, double>> transactionList;

public:
    Order(const std::string &id, char t, int qty, double pr = -1.0);
    
    std::string getOrderID() const;
    char getType() const;
    int getQuantity() const;
    double getPrice() const;
    bool priceAvailable() const;
    bool priceAcceptable(double price) const;
    std::vector<Transaction<std::string, double>> getTransactionList() const;
    int quantityAvailable() const;
    void add_transaction(const Transaction<std::string, double> &trade);
    void display() const;
};

#endif // ORDER_H
