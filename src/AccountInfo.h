#include <string>
#include <iostream>


class AccountInfo{
public:
    std::string Account;
    std::string AccountType;
    std::string Currency;
    int Cushion;
    int DayTradesRemaining;
    int LookAheadNextChange;
    int AccruedCash;
    float AvailableFunds;
    float BuyingPower;
    float EquityWithLoanValue;
    float ExcessLiquidity;
    float FullAvailableFunds;
    float FullExcessLiquidity;
    float FullInitMarginReq;
    float FullMaintMarginReq;
    float GrossPositionValue;
    float InitMarginReq;
    float LookAheadAvailableFunds;
    float LookAheadExcessLiquidity;
    float LookAheadInitMarginReq;
    float LookAheadMaintMarginReq;
    float MaintMarginReq;
    float NetLiquidation;
    float SMA;
    float TotalCashValue;

    void displayAccountInfo();
};