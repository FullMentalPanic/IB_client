#include "Order.h"


#include <vector>
#include <string>

class SymbolOrders
{
public:    
    SymbolOrders(/* args */);
    ~SymbolOrders();
    SymbolOrders(int);
    std::vector<Order> orders;
    std::vector<int> status_s;
    std::vector<long> orderIDs;
};


