#include "transaction.h"

Transaction::Transaction(const std::string &id, char t, int qty, double pr)
    : orderID(id), type(t), quantity(qty), price(pr) {}

std::string Transaction::getOrderID() const { return orderID; }
char Transaction::getType() const { return type; }
int Transaction::getQuantity() const { return quantity; }
double Transaction::getPrice() const { return price; }
