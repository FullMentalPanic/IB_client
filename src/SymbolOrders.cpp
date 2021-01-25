#include "SymbolOrders.h"

SymbolOrders::SymbolOrders(/* args */)
{
}

SymbolOrders::SymbolOrders(int n)
{
    for (int i = 0; i < n; i++){
        orders.push_back(Order());
        status_s.push_back(0);
        orderIDs.push_back(0);
    }
}

SymbolOrders::~SymbolOrders()
{
    orders.clear();
    status_s.clear();
    orderIDs.clear();

    orders.shrink_to_fit();
    status_s.shrink_to_fit();
    orderIDs.shrink_to_fit();
}