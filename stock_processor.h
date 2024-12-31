#ifndef STOCKPROCESSOR_h
#define STOCKPROCESSOR_h

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

class StockProcessor
{
public:
    StockProcessor(const std::string &filename, const std::string &outputfilename);
    ~StockProcessor();

    void process();

private:
    std::ifstream file;
    std::ofstream newFile;
    std::deque<Order> orders;
    float previousPrice;
    void writeLogForOrderExecution(std::deque<Transaction> transactionList, std::ofstream &newFile);
    void matchOrders(Order &newOrder, Order &previousOrder, float *previousPrice, std::ofstream &newFile);
    void writeFinalLogForUnexecutedOrders(const std::deque<Order> &orders, std::ofstream &newFile);  
    void removeCompletedOrdersFromList(std::deque<Order> &orders);
    void processOrder(Order &order, float *previousPrice, std::deque<Order> &orders, std::ofstream &newFile);  
};

#endif 