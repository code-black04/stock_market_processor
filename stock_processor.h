#ifndef STOCK_PROCESSOR_H
#define STOCK_PROCESSOR_H

#include <fstream>
#include <string>
#include "order.h"
#include "transaction.h"

class StockProcessor
{
public:
    StockProcessor(const std::string &filename, const std::string &outputFilename);
    ~StockProcessor();

    void process();

private:
    std::ifstream file;
    std::ofstream newFile;
    std::deque<Order> pendingOrders;
    float previousPrice;
    void writeLogForOrderExecution(std::vector<Transaction<std::string, double>> transactionList, std::ofstream &newFile);
    void matchOrders(Order &newOrder, Order &previousOrder, float *previousPrice, std::ofstream &newFile);
    void writeFinalLogForUnexecutedOrders(const std::deque<Order> &pendingOrders, std::ofstream &newFile);  
    void removeCompletedOrdersFromList(std::deque<Order> &pendingOrders);
    void processOrder(Order &order, float *previousPrice, std::deque<Order> &pendingOrders, std::ofstream &newFile);  
};

#endif // STOCK_PROCESSOR_H