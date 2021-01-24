#include "AccountInfo.h"

using namespace std;

void AccountInfo::displayAccountInfo(){

    cout << "Account :" << Account << endl;
    cout << "AccountType :" << AccountType << endl;
    cout << "Currency :" << Currency << endl;
    cout << "Cushion :" << Cushion << endl;
    cout << "DayTradesRemaining :" << DayTradesRemaining << endl;
    cout << "LookAheadNextChange :" << LookAheadNextChange << endl;
    cout << "AccruedCash :" << AccruedCash << endl;
    cout << "AvailableFunds :" << fixed << AvailableFunds << endl;
    cout << "BuyingPower :" << fixed << BuyingPower << endl;
    cout << "EquityWithLoanValue :" << fixed << EquityWithLoanValue << endl;
    cout << "ExcessLiquidity :" << fixed << ExcessLiquidity << endl;
    cout << "FullAvailableFunds :" << fixed << FullAvailableFunds << endl;
    cout << "FullExcessLiquidity :" << fixed << FullExcessLiquidity << endl;
    cout << "FullInitMarginReq :" << fixed << FullInitMarginReq << endl;
    cout << "FullMaintMarginReq :" << fixed << FullMaintMarginReq << endl;
    cout << "GrossPositionValue :" << fixed << GrossPositionValue << endl;
    cout << "InitMarginReq :" << fixed << InitMarginReq << endl;
    cout << "LookAheadAvailableFunds :" << fixed << LookAheadAvailableFunds << endl;
    cout << "LookAheadInitMarginReq :" << fixed << LookAheadInitMarginReq << endl;
    cout << "LookAheadExcessLiquidity :" << fixed << LookAheadExcessLiquidity << endl;
    cout << "LookAheadMaintMarginReq :" << fixed << LookAheadMaintMarginReq << endl;
    cout << "MaintMarginReq :" << fixed << MaintMarginReq << endl;
    cout << "NetLiquidation :" << fixed << NetLiquidation << endl;
    cout << "SMA :" << fixed << SMA << endl;
    cout << "TotalCashValue :" << fixed << TotalCashValue << endl;
}