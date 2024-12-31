#include "stock_processor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <float.h>
#include "order.h"
#include <iomanip>
#include <algorithm>
#include <deque>
#include <string>
#include <regex>
#include "transaction.h"

StockProcessor::StockProcessor(const std::string &filename, const std::string &outputfilename)
    : file(filename), newFile(outputfilename), orders(), previousPrice(0.00f)
{
    if (!file.is_open())
    {
        std::cerr << "Failed to open the input file." << std::endl;
        exit(1);
    }
    if (!newFile.is_open())
    {
        std::cerr << "Failed to open the output file." << std::endl;
        exit(1);
    }
}

StockProcessor::~StockProcessor()
{
    file.close();
    newFile.close();
}

void StockProcessor::process()
{
    std::string line;
    bool firstLine = true;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        if (firstLine)
        {
            iss >> previousPrice;
            firstLine = false;
            continue;
        }

        std::string id;
        char type;
        int quantity;
        double price = -1.0;

        // Parse line
        if (iss >> id >> type >> quantity)
        {
            iss >> price;
            Order order(id, type, quantity, price);
            processOrder(order, &previousPrice, orders, newFile);
        }
        removeCompletedOrdersFromList(orders);
    }

    writeFinalLogForUnexecutedOrders(orders, newFile);
}

void StockProcessor::writeFinalLogForUnexecutedOrders(const std::deque<Order> &orders, std::ofstream &newFile)
{
    for (const auto &order : orders)
    {
        if (order.quantityAvailable() > 0)
        {
            std::cout << "order " << order.getOrderID() << " " << order.quantityAvailable() << " shares unexecuted" << std::endl;
            newFile << "order " << order.getOrderID() << " " << order.quantityAvailable() << " shares unexecuted" << std::endl;
        }
    }
}

void StockProcessor::writeLogForOrderExecution(std::deque<Transaction> trades, std::ofstream &newFile)
{
    std::sort(trades.begin(), trades.end(), [](const Transaction &a, const Transaction &b)
              { return a.getType() < b.getType(); });
    for (const auto &o : trades)
    {
        if (o.getType() == 'B')
        {
            std::cout << "order " << o.getOrderID() << " " << o.getQuantity() << " shares purchased at price " << o.getPrice() << std::endl;
            newFile << "order " << o.getOrderID() << " " << o.getQuantity() << " shares purchased at price " << o.getPrice() << std::endl;
        }
        else
        {
            std::cout << "order " << o.getOrderID() << " " << o.getQuantity() << " shares sold at price " << o.getPrice() << std::endl;
            newFile << "order " << o.getOrderID() << " " << o.getQuantity() << " shares sold at price " << o.getPrice() << std::endl;
        }
    }
}

void StockProcessor::matchOrders(Order &newOrder, Order &previousOrder, float *previousPrice, std::ofstream &newFile)
{
    double price;
    if (newOrder.priceAvailable() && previousOrder.priceAvailable())
    {
        price = previousOrder.getPrice();
    }
    else if (newOrder.priceAvailable())
    {
        price = newOrder.getPrice();
    }
    else if (previousOrder.priceAvailable())
    {
        price = previousOrder.getPrice();
    }
    else
    {
        price = *previousPrice;
    }

    int minQuantity = std::min(newOrder.quantityAvailable(), previousOrder.quantityAvailable());
    if (newOrder.priceAcceptable(price) && minQuantity > 0)
    {
        newOrder.add_transaction(Transaction(previousOrder.getOrderID(), previousOrder.getType(), minQuantity, price));
        previousOrder.add_transaction(Transaction(newOrder.getOrderID(), newOrder.getType(), minQuantity, price));
        writeLogForOrderExecution({newOrder.getTransactionList().back(), previousOrder.getTransactionList().back()}, newFile);
        *previousPrice = price;
    }
}

void StockProcessor::removeCompletedOrdersFromList(std::deque<Order> &orders)
{
    for (auto it = orders.begin(); it != orders.end(); ++it)
    {
        if (it->quantityAvailable() <= 0)
        {
            orders.erase(it);
            break;
        }
    }
}

void StockProcessor::processOrder(Order &order, float *previousPrice, std::deque<Order> &orders, std::ofstream &newFile)
{
    std::vector<Order *> buyOrders = {};
    std::vector<Order *> sellOrders = {};

    for (auto &torder : orders)
    {
        if (torder.getType() == 'B' && torder.priceAvailable())
            buyOrders.push_back(&torder);
        else if (torder.getType() == 'S' && torder.priceAvailable())
            sellOrders.push_back(&torder);

        // match market orders first
        if (order.getType() != torder.getType() && !torder.priceAvailable())
        {
            matchOrders(order, torder, previousPrice, newFile);
        }

        if (order.quantityAvailable() <= 0)
            return;
    }

    // sort pending buy orders by high price first
    std::sort(buyOrders.begin(), buyOrders.end(), [](const Order *a, const Order *b)
              { return a->getPrice() > b->getPrice(); });
    // sort pending sell orders by low price first
    std::sort(sellOrders.begin(), sellOrders.end(), [](const Order *a, const Order *b)
              { return a->getPrice() < b->getPrice(); });

    std::vector<Order *> targetOrders = order.getType() == 'S' ? buyOrders : sellOrders;
    for (auto &torder : targetOrders)
    { // match non market orders
        if (order.getType() != torder->getType())
        {
            matchOrders(order, *torder, previousPrice, newFile);
        }
    }
    if (order.quantityAvailable() > 0)
    {
        orders.push_back(order);
    }
}