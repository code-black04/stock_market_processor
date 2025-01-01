#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>

template <typename IDType, typename PriceType>

class Transaction
{
private:
    IDType orderID;
    char type; // 'B' for Buy, 'S' for Sell
    int quantity;
    PriceType price;

public:
    Transaction(const IDType &id, char t, int qty, PriceType pr);

    IDType getOrderID() const;
    char getType() const;
    int getQuantity() const;
    PriceType getPrice() const;
};

#include "transaction.tpp" // Include template implementation

#endif //TRANSACTION_H
