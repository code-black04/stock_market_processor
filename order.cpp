#include "order.h"
#include "transaction.h"


Order::Order(const std::string &id, char t, int qty, double pr)
    : orderID(id), type(t), quantity(qty), price(pr), hasPrice(pr != -1.0), transactionList({}) {}

std::string Order::getOrderID() const { return orderID; }
char Order::getType() const { return type; }
int Order::getQuantity() const { return quantity; }
double Order::getPrice() const { return price; }
bool Order::priceAvailable() const { return hasPrice; }
std::vector<Transaction<std::string, double>> Order::getTransactionList() const { return transactionList; }

// Utility Function
void Order::display() const
{
    std::cout << "Order ID: " << orderID
              << ", Type: " << (type == 'B' ? "Buy" : "Sell")
              << ", Quantity: " << quantity;
    if (hasPrice)
    {
        std::cout << ", Price: $" << std::fixed << std::setprecision(2) << price;
    }
    else
    {
        std::cout << ", Price: Not Provided";
    }
    std::cout << std::endl;
}

bool Order::priceAcceptable(double price) const
{
    if (priceAvailable())
    {
        if (type == 'B' && price <= this->price)
        {
            return true;
        }
        else if (type == 'S' && price >= this->price)
        {
            return true;
        }
        return false;
    }
    return true;
}

int Order::quantityAvailable() const
{
    int quantityTraded = 0;
    for (const auto &trade : transactionList)
    {
        quantityTraded += trade.getQuantity();
    }
    return (getQuantity() - quantityTraded);
}
void Order::add_transaction(const Transaction<std::string, double> &trade)
{
    transactionList.push_back(trade);
}