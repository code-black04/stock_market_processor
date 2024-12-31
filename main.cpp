#include "stock_processor.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "incorrect program arguments, expected 2... existing program execution..." << std::endl;
        return 1;
    }

    std::string outputfilename = argv[1];
    std::regex numberRegex("\\d+");
    std::smatch match;

    if (std::regex_search(outputfilename, match, numberRegex))
    {
        std::cout << "Extracted number: " << match.str() << std::endl;
    }
    else
    {
        std::cout << "No number found in the filename." << std::endl;
    }

    outputfilename = "output" + match.str() + ".txt";
    StockProcessor processor(argv[1], outputfilename);
    processor.process();

    return 0;
}
