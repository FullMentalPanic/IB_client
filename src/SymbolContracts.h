#include "Contract.h"

#include <string>
#include <vector>



class SymbolContracts
{
private:
    void read_csv(std::string filename, int basetickID = 0);
public:
    SymbolContracts(std::string, int);
    SymbolContracts(std::string);
    SymbolContracts();
    ~SymbolContracts();
    std::vector <long> tickIDs;
    std::vector <Contract> contracts;
    std::vector <int> BidSize;
    std::vector <double> BidPrice;
    std::vector <double> AskPrice;
    std::vector <double> AskSize;
    std::vector <double> LastPrice;
    int total;

    void DisplayContracts();
    void DisplayPrice();
};

