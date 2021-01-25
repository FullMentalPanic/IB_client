/*
base Class to process recv info
*/

#include "TWS_Client.h"
#include "EClientSocket.h"
#include "Order.h"
#include "OrderState.h"

#include "AccountSummaryTags.h"
#include "TickType.h"
#include "OrderSamples.h"


#include <thread>

#define DEBUG
#define SELL_TEST

TWS_Client::TWS_Client(){
    m_osSignal = EReaderOSSignal(2000);
    m_pClient  = new EClientSocket(this, &m_osSignal);
    m_orderId = 0;
	m_extraAuth = false;

	baseTickerId = 0;
	myContracts = SymbolContracts("Contract.csv",baseTickerId);
	myOrders = SymbolOrders(myContracts.total);
}

TWS_Client::~TWS_Client(){
	if( m_pReader )
		m_pReader.reset();

	delete m_pClient;
}



bool TWS_Client::connect(const char * host, int port, int clientId){	
	bool bRes = m_pClient->eConnect( host, port, clientId, m_extraAuth);
	
	if (bRes) {
		printf( "Connected to %s:%d clientId:%d\n", m_pClient->host().c_str(), m_pClient->port(), clientId);
		m_pReader = std::unique_ptr<EReader>( new EReader(m_pClient, &m_osSignal) );
		m_pReader->start();

		boost::function0<void> f = boost::bind(&TWS_Client::run, this);
		boost::thread t(f);
		worker = &t;		
	}
	else
		printf( "Cannot connect to %s:%d clientId:%d\n", m_pClient->host().c_str(), m_pClient->port(), clientId);

	return bRes;
}

void TWS_Client::disconnect(){

	m_pClient->eDisconnect();
	worker->interrupt();//end thread
	worker->join();//end thread
	printf ( "Disconnected\n");
}

bool TWS_Client::isConnected(){
	return m_pClient->isConnected();

}

void TWS_Client::setConnectOptions(const std::string& connectOptions){
	m_pClient->setConnectOptions(connectOptions);
}

void TWS_Client::init(){
	m_pClient->reqManagedAccts();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	m_pClient->reqAccountSummary(9001, "All", AccountSummaryTags::getAllTags());
	std::this_thread::sleep_for(std::chrono::seconds(2));
	m_pClient->cancelAccountSummary(9001);

}

void TWS_Client::updateCashandBuyPower(){
	m_pClient->reqAccountSummary(9002, "All", AccountSummaryTags::BuyingPower);
	std::this_thread::sleep_for(std::chrono::seconds(2));
	m_pClient->reqAccountSummary(9003, "All", AccountSummaryTags::TotalCashValue);
	std::this_thread::sleep_for(std::chrono::seconds(2));
	m_pClient->cancelAccountSummary(9002);
	m_pClient->cancelAccountSummary(9003);

}

void TWS_Client::test(){
	
	m_pClient->reqManagedAccts();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	m_pClient->reqAccountSummary(9001, "All", AccountSummaryTags::getAllTags());
	std::this_thread::sleep_for(std::chrono::seconds(2));
	m_pClient->cancelAccountSummary(9001);

	myAccountInfo.displayAccountInfo();
	myContracts.DisplayContracts();
	

	for (int i = 0; i < myContracts.total; i++){
		m_pClient->reqMktData(myContracts.tickIDs[i], myContracts.contracts[i], "", false, false, TagValueListSPtr());
	}
	

	std::this_thread::sleep_for(std::chrono::seconds(2));
	myContracts.DisplayPrice();

	while(myContracts.AskPrice[0] < 0.1){
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	

	#ifdef BUY_TEST
	Order myOrder;
	// Test BUY 
	for (int i = 0; i < myContracts.total; i++){
		myOrder = OrderSamples::LimitOrder("BUY", 1, myContracts.AskPrice[i]);
		m_pClient->placeOrder(m_orderId++, myContracts.contracts[i], myOrder);
	}
	#endif

	#ifdef SELL_TEST
	Order myOrder;
	// Test SELL 
	for (int i = 0; i < myContracts.total; i++){
		myOrders.orderIDs[i] = m_orderId;
		myOrders.orders[i] = OrderSamples::LimitOrder("SELL", 1, myContracts.AskPrice[i]);
		//myOrder = OrderSamples::LimitOrder("SELL", 1, myContracts.AskPrice[i]);
		m_pClient->placeOrder(m_orderId++, myContracts.contracts[i], myOrders.orders[i]);
	}
	#endif

	std::this_thread::sleep_for(std::chrono::seconds(2));

}

void TWS_Client::run(){
	while (m_pClient-> isConnected()){
		m_osSignal.waitForSignal();
		m_pReader->processMsgs();
	}
}

void TWS_Client::connectAck() {
	if (!m_extraAuth && m_pClient->asyncEConnect())
        m_pClient->startApi();
}

void TWS_Client::connectionClosed(){
	printf("Connection Close\n");
	throw (NET_CLOSE);
}

void TWS_Client::winError( const std::string& str, int lastError) {}
void TWS_Client::error(int id, int errorCode, const std::string& errorString) {
	printf( "Error. Id: %d, Code: %d, Msg: %s\n", id, errorCode, errorString.c_str());	
}

void TWS_Client::nextValidId( OrderId orderId){
	#ifdef DEBUG
	printf("Next Valid Id: %ld\n", orderId);
	#endif
	m_orderId = orderId;
}

void TWS_Client::accountSummary( int reqId, const std::string& account, const std::string& tag, const std::string& value, const std::string& curency) {
	#ifdef DEBUG
	printf( "Acct Summary. ReqId: %d, Account: %s, Tag: %s, Value: %s, Currency: %s\n", reqId, account.c_str(), tag.c_str(), value.c_str(), curency.c_str());
	#endif
	if (tag == "BuyingPower"){
		myAccountInfo.BuyingPower = std::stof(value);
		return;
	}
	if (tag == "TotalCashValue"){
		myAccountInfo.TotalCashValue = std::stof(value);
		myAccountInfo.Currency = curency;
		return;
	}
	if (tag == "AccountType"){
		myAccountInfo.Account = account;
		myAccountInfo.AccountType = value;
		return;
	}
	if (tag == "Cushion"){
		myAccountInfo.Cushion = std::stoi(value);
		return;
	}
	if (tag == "DayTradesRemaining"){
		myAccountInfo.DayTradesRemaining = std::stoi(value);
		return;
	}
	if (tag == "LookAheadNextChange"){
		myAccountInfo.LookAheadNextChange = std::stoi(value);
		return;
	}
	if (tag == "AccruedCash"){
		myAccountInfo.AccruedCash = std::stof(value);
		return;
	}
	if (tag == "AvailableFunds"){
		myAccountInfo.AvailableFunds = std::stof(value);
		return;
	}
	if (tag == "EquityWithLoanValue"){
		myAccountInfo.EquityWithLoanValue = std::stof(value);
		return;
	}
	if (tag == "ExcessLiquidity"){
		myAccountInfo.ExcessLiquidity = std::stof(value);
		return;
	}
	if (tag == "FullAvailableFunds"){
		myAccountInfo.FullAvailableFunds = std::stof(value);
		return;
	}
	if (tag == "FullExcessLiquidity"){
		myAccountInfo.FullExcessLiquidity = std::stof(value);
		return;
	}
	if (tag == "FullInitMarginReq"){
		myAccountInfo.FullInitMarginReq = std::stof(value);
		return;
	}
	if (tag == "GrossPositionValue"){
		myAccountInfo.GrossPositionValue = std::stof(value);
		return;
	}
	if (tag == "InitMarginReq"){
		myAccountInfo.InitMarginReq = std::stof(value);
		return;
	}
	if (tag == "LookAheadAvailableFunds"){
		myAccountInfo.LookAheadAvailableFunds = std::stof(value);
		return;
	}
	if (tag == "LookAheadExcessLiquidity"){
		myAccountInfo.LookAheadExcessLiquidity = std::stof(value);
		return;
	}
	if (tag == "LookAheadInitMarginReq"){
		myAccountInfo.LookAheadInitMarginReq = std::stof(value);
		return;
	}
	if (tag == "LookAheadMaintMarginReq"){
		myAccountInfo.LookAheadMaintMarginReq = std::stof(value);
		return;
	}
	if (tag == "MaintMarginReq"){
		myAccountInfo.MaintMarginReq = std::stof(value);
		return;
	}
	if (tag == "NetLiquidation"){
		myAccountInfo.NetLiquidation = std::stof(value);
		return;
	}
	if (tag == "SMA"){
		myAccountInfo.SMA = std::stof(value);
		return;
	}
}


void TWS_Client::tickPrice( TickerId tickerId, TickType field, double price, const TickAttrib& attrib) {
	#ifdef DEBUG
	printf( "Tick Price. Ticker Id: %ld, Field: %d, Price: %g, CanAutoExecute: %d, PastLimit: %d, PreOpen: %d\n", tickerId, (int)field, price, attrib.canAutoExecute, attrib.pastLimit, attrib.preOpen);
	#endif
	int num = tickerId - baseTickerId;
	if (myContracts.total <= num){
		return;
	}
	switch (field){
		case BID_PRICE:
			myContracts.BidPrice[num] = price;
			return;
		case ASK_PRICE:
			myContracts.AskPrice[num] = price;
			return;
		case LAST_PRICE:
			myContracts.LastPrice[num] = price;
			return;
		case HIGH:
			/* code */
			return;
		case LOW:
			/* code */
			return;
		case CLOSE_PRICE:
			/* code */
			return;
		case OPEN_TICK:
			/* code */
			return;
		case LOW_13_WEEKS:
			/* code */
			return;
		case HIGH_13_WEEKS:
			/* code */
			return;
		case LOW_26_WEEKS:
			/* code */
			return;
		case HIGH_26_WEEKS:
			/* code */
			return;
		case LOW_52_WEEKS:
			/* code */
			return;
		case HIGH_52_WEEKS:
			/* code */
			return;
		case AUCTION_PRICE:
			/* code */
			return;
		case MARK_PRICE:
			/* code */
			return;
		case BID_YIELD:
			/* code */
			return;
		case ASK_YIELD:
			/* code */
			return;
		case LAST_YIELD:
			/* code */
			return;
		case LAST_RTH_TRADE:
			/* code */
			return;
		case DELAYED_BID:
			/* code */
			return;
		case DELAYED_ASK:
			/* code */
			return;
		case DELAYED_LAST:
			/* code */
			return;
		case DELAYED_HIGH_PRICE:
			/* code */
			return;
		case DELAYED_LOW_PRICE:
			/* code */
			return;
		case DELAYED_CLOSE:
			/* code */
			return;
		case DELAYED_OPEN:
			/* code */
			return;
		case CREDITMAN_MARK_PRICE:
			/* code */
			return;
		case CREDITMAN_SLOW_MARK_PRICE:
			/* code */
			return;
		case DELAYED_BID_OPTION:
			/* code */
			return;
		case DELAYED_ASK_OPTION:
			/* code */
			return;
		case DELAYED_LAST_OPTION:
			/* code */
			return;
		case DELAYED_MODEL_OPTION:
			/* code */
			return;
		case ETF_NAV_CLOSE:
			/* code */
			return;
		case ETF_NAV_PRIOR_CLOSE:
			/* code */
			return;
		case ETF_NAV_BID:
			/* code */
			return;
		case ETF_NAV_ASK:
			/* code */
			return;
		case ETF_NAV_LAST:
			/* code */
			return;
		case ETF_NAV_FROZEN_LAST:
			/* code */
			return;
		case ETF_NAV_HIGH:
			/* code */
			return;	
		case ETF_NAV_LOW:
			/* code */
			return;						
		default:
			return;
	}
}

void TWS_Client::tickSize( TickerId tickerId, TickType field, int size) {
	#ifdef DEBUG
	printf( "Tick Size. Ticker Id: %ld, Field: %d, Size: %d\n", tickerId, (int)field, size);
	#endif
	int num = tickerId - baseTickerId;
	if (myContracts.total <= num){
		return;
	}
	switch (field){
		case BID_SIZE:
			myContracts.BidSize[num] = size;
			return;
		case ASK_SIZE:
			myContracts.AskSize[num] = size;
			return;
		case LAST_SIZE:
			/* code */
			return;
		case VOLUME:
			/* code */
			return;
		case AVERAGE_VOLUME:
			/* code */
			return;
		case AUCTION_IMBALANCE:
			/* code */
			return;
		case OPEN_INTEREST:
			/* code */
			return;
		case OPTION_CALL_OPEN_INTEREST:
			/* code */
			return;
		case OPTION_PUT_OPEN_INTEREST:
			/* code */
			return;
		case OPTION_CALL_VOLUME:
			/* code */
			return;
		case OPTION_PUT_VOLUME:
			/* code */
			return;
		case AUCTION_VOLUME:
			/* code */
			return;
		case REGULATORY_IMBALANCE:
			/* code */
			return;
		case SHORT_TERM_VOLUME_3_MINUTES:
			/* code */
			return;
		case SHORT_TERM_VOLUME_5_MINUTES:
			/* code */
			return;
		case SHORT_TERM_VOLUME_10_MINUTES:
			/* code */
			return;
		case DELAYED_BID_SIZE:
			/* code */
			return;
		case DELAYED_ASK_SIZE:
			/* code */
			return;
		case DELAYED_LAST_SIZE:
			/* code */
			return;
		case DELAYED_VOLUME:
			/* code */
			return;
		case FUTURES_OPEN_INTEREST:
			/* code */
			return;
		case AVERAGE_OPTION_VOLUME:
			/* code */
			return;
		case SHORTABLE_SHARES:
			/* code */
			return;				
		default:
			return;
	}
}

void TWS_Client::tickOptionComputation( TickerId tickerId, TickType tickType, int tickAttrib, double impliedVol, double delta,
	double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice) {
	#ifdef DEBUG
	printf( "TickOptionComputation. Ticker Id: %ld, Type: %d, TickAttrib: %d, ImpliedVolatility: %g, Delta: %g, OptionPrice: %g, pvDividend: %g, Gamma: %g, Vega: %g, Theta: %g, Underlying Price: %g\n", tickerId, (int)tickType, tickAttrib, impliedVol, delta, optPrice, pvDividend, gamma, vega, theta, undPrice);
	#endif
	switch (tickType){
		case BID_OPTION_COMPUTATION:
			/* code */
			return;
		case ASK_OPTION_COMPUTATION:
			/* code */
			return;
		case LAST_OPTION_COMPUTATION:
			/* code */
			return;
		case MODEL_OPTION_COMPUTATION:
			/* code */
			return;
		case CUSTOM_OPTION_COMPUTATION:
			/* code */
			return;
		default:
			return;
	}	

}

void TWS_Client::tickGeneric(TickerId tickerId, TickType tickType, double value) {
	#ifdef DEBUG
		printf( "Tick Generic. Ticker Id: %ld, Type: %d, Value: %g\n", tickerId, (int)tickType, value);
	#endif
	switch (tickType){
		case OPTION_HISTORICAL_VOLATILITY:
			/* code */
			return;
		case OPTION_IMPLIED_VOLATILITY:
			/* code */
			return;
		case INDEX_FUTURE_PREMIUM:
			/* code */
			return;
		case SHORTABLE:
			/* code */
			return;
		case HALTED:
			/* code */
			return;
		case TRADE_COUNT:
			/* code */
			return;
		case TRADE_RATE:
			/* code */
			return;
		case VOLUME_RATE:
			/* code */
			return;
		case RT_HISTORICAL_VOLATILITY:
			/* code */
			return;
		case BOND_FACTOR_MULTIPLIER:
			/* code */
			return;
		default:
			return;
	}	
}

void TWS_Client::tickString(TickerId tickerId, TickType tickType, const std::string& value) {
	#ifdef DEBUG
	printf( "Tick String. Ticker Id: %ld, Type: %d, Value: %s\n", tickerId, (int)tickType, value.c_str());
	#endif
	switch (tickType){
		case OPTION_BID_EXCHANGE:
			/* code */
			return;
		case OPTION_ASK_EXCHANGE:
			/* code */
			return;
		case BID_EXCHANGE:
			/* code */
			return;
		case ASK_EXCHANGE:
			/* code */
			return;
		case LAST_TIMESTAMP:
			/* code */
			return;
		case RT_VOLUME_TIME_SALES:
			/* code */
			return;
		case IB_DIVIDENDS:
			/* code */
			return;
		case NEWS:
			/* code */
			return;
		case RT_TRADE_VOLUME:
			/* code */
			return;
		case LAST_EXCHANGE:
			/* code */
			return;
		case LAST_REGULATORY_TIME:
			/* code */
			return;
		case DELAYED_LAST_TIMESTAMP:
			/* code */
			return;
		default:
			return;
	}		
}

void TWS_Client::tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const std::string& formattedBasisPoints,
	double totalDividends, int holdDays, const std::string& futureLastTradeDate, double dividendImpact, double dividendsToLastTradeDate) {
	#ifdef DEBUG
	printf( "TickEFP. %ld, Type: %d, BasisPoints: %g, FormattedBasisPoints: %s, Total Dividends: %g, HoldDays: %d, Future Last Trade Date: %s, Dividend Impact: %g, Dividends To Last Trade Date: %g\n", tickerId, (int)tickType, basisPoints, formattedBasisPoints.c_str(), totalDividends, holdDays, futureLastTradeDate.c_str(), dividendImpact, dividendsToLastTradeDate);
	#endif
	switch (tickType){
		case BID_EFP_COMPUTATION:
			/* code */
			return;
		case ASK_EFP_COMPUTATION:
			/* code */
			return;
		case LAST_EFP_COMPUTATION:
			/* code */
			return;
		case OPEN_EFP_COMPUTATION:
			/* code */
			return;
		case HIGH_EFP_COMPUTATION:
			/* code */
			return;
		case LOW_EFP_COMPUTATION:
			/* code */
			return;
		case CLOSE_EFP_COMPUTATION:
			/* code */
			return;
		default:
			return;
	}		
}

void TWS_Client::orderStatus( OrderId orderId, const std::string& status, double filled,
	double remaining, double avgFillPrice, int permId, int parentId,
	double lastFillPrice, int clientId, const std::string& whyHeld, double mktCapPrice) {
	#ifdef DEBUG
	printf("OrderStatus. Id: %ld, Status: %s, Filled: %g, Remaining: %g, AvgFillPrice: %g, PermId: %d, LastFillPrice: %g, ClientId: %d, WhyHeld: %s, MktCapPrice: %g\n", 
	orderId, status.c_str(), filled, remaining, avgFillPrice, permId, lastFillPrice, clientId, whyHeld.c_str(), mktCapPrice);
	#endif
}


void TWS_Client::openOrder( OrderId orderId, const Contract& contract, const Order& order, const OrderState& orderState) {
	#ifdef DEBUG
	printf( "OpenOrder. PermId: %i, ClientId: %ld, OrderId: %ld, Account: %s, Symbol: %s, SecType: %s, Exchange: %s:, Action: %s, OrderType:%s, TotalQty: %g, CashQty: %g, "
	"LmtPrice: %g, AuxPrice: %g, Status: %s\n", 
		order.permId, order.clientId, orderId, order.account.c_str(), contract.symbol.c_str(), contract.secType.c_str(), contract.exchange.c_str(), 
		order.action.c_str(), order.orderType.c_str(), order.totalQuantity, order.cashQty == UNSET_DOUBLE ? 0 : order.cashQty, order.lmtPrice, order.auxPrice, orderState.status.c_str());
	#endif

}

void TWS_Client::openOrderEnd() {
	#ifdef DEBUG
	printf( "OpenOrderEnd\n");
	#endif
}

void TWS_Client::updateAccountValue(const std::string& key, const std::string& val,
const std::string& currency, const std::string& accountName) {}
void TWS_Client::updatePortfolio( const Contract& contract, double position,
	double marketPrice, double marketValue, double averageCost,
	double unrealizedPNL, double realizedPNL, const std::string& accountName) {}
void TWS_Client::updateAccountTime(const std::string& timeStamp) {}
void TWS_Client::accountDownloadEnd(const std::string& accountName) {}
void TWS_Client::contractDetails( int reqId, const ContractDetails& contractDetails) {}
void TWS_Client::bondContractDetails( int reqId, const ContractDetails& contractDetails) {}
void TWS_Client::contractDetailsEnd( int reqId) {}
void TWS_Client::execDetails( int reqId, const Contract& contract, const Execution& execution) {}
void TWS_Client::execDetailsEnd( int reqId) {}
void TWS_Client::updateMktDepth(TickerId id, int position, int operation, int side,
	double price, int size) {}
void TWS_Client::updateMktDepthL2(TickerId id, int position, const std::string& marketMaker, int operation,
	int side, double price, int size, bool isSmartDepth) {}
void TWS_Client::updateNewsBulletin(int msgId, int msgType, const std::string& newsMessage, const std::string& originExch) {}
void TWS_Client::managedAccounts( const std::string& accountsList) {}
void TWS_Client::receiveFA(faDataType pFaDataType, const std::string& cxml) {}
void TWS_Client::historicalData(TickerId reqId, const Bar& bar) {}
void TWS_Client::historicalDataEnd(int reqId, const std::string& startDateStr, const std::string& endDateStr) {}
void TWS_Client::scannerParameters(const std::string& xml) {}
void TWS_Client::scannerData(int reqId, int rank, const ContractDetails& contractDetails,
	const std::string& distance, const std::string& benchmark, const std::string& projection,
	const std::string& legsStr) {}
void TWS_Client::scannerDataEnd(int reqId) {}
void TWS_Client::realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
	long volume, double wap, int count) {}
void TWS_Client::currentTime(long time) {}
void TWS_Client::fundamentalData(TickerId reqId, const std::string& data) {}
void TWS_Client::deltaNeutralValidation(int reqId, const DeltaNeutralContract& deltaNeutralContract) {}
void TWS_Client::tickSnapshotEnd( int reqId) {}
void TWS_Client::marketDataType( TickerId reqId, int marketDataType) {}
void TWS_Client::commissionReport( const CommissionReport& commissionReport) {}
void TWS_Client::position( const std::string& account, const Contract& contract, double position, double avgCost) {}
void TWS_Client::positionEnd() {}

void TWS_Client::accountSummaryEnd( int reqId) {}
void TWS_Client::verifyMessageAPI( const std::string& apiData) {}
void TWS_Client::verifyCompleted( bool isSuccessful, const std::string& errorText) {}
void TWS_Client::displayGroupList( int reqId, const std::string& groups) {}
void TWS_Client::displayGroupUpdated( int reqId, const std::string& contractInfo) {}
void TWS_Client::verifyAndAuthMessageAPI( const std::string& apiData, const std::string& xyzChallange) {}
void TWS_Client::verifyAndAuthCompleted( bool isSuccessful, const std::string& errorText) {}
void TWS_Client::positionMulti( int reqId, const std::string& account,const std::string& modelCode, const Contract& contract, double pos, double avgCost) {}
void TWS_Client::positionMultiEnd( int reqId) {}
void TWS_Client::accountUpdateMulti( int reqId, const std::string& account, const std::string& modelCode, const std::string& key, const std::string& value, const std::string& currency) {}
void TWS_Client::accountUpdateMultiEnd( int reqId) {}
void TWS_Client::securityDefinitionOptionalParameter(int reqId, const std::string& exchange, int underlyingConId, const std::string& tradingClass,
	const std::string& multiplier, const std::set<std::string>& expirations, const std::set<double>& strikes) {}
void TWS_Client::securityDefinitionOptionalParameterEnd(int reqId) {}
void TWS_Client::softDollarTiers(int reqId, const std::vector<SoftDollarTier> &tiers) {}
void TWS_Client::familyCodes(const std::vector<FamilyCode> &familyCodes) {}
void TWS_Client::symbolSamples(int reqId, const std::vector<ContractDescription> &contractDescriptions) {}
void TWS_Client::mktDepthExchanges(const std::vector<DepthMktDataDescription> &depthMktDataDescriptions) {}
void TWS_Client::tickNews(int tickerId, time_t timeStamp, const std::string& providerCode, const std::string& articleId, const std::string& headline, const std::string& extraData) {}
void TWS_Client::smartComponents(int reqId, const SmartComponentsMap& theMap) {}
void TWS_Client::tickReqParams(int tickerId, double minTick, const std::string& bboExchange, int snapshotPermissions) {}
void TWS_Client::newsProviders(const std::vector<NewsProvider> &newsProviders) {}
void TWS_Client::newsArticle(int requestId, int articleType, const std::string& articleText) {}
void TWS_Client::historicalNews(int requestId, const std::string& time, const std::string& providerCode, const std::string& articleId, const std::string& headline) {}
void TWS_Client::historicalNewsEnd(int requestId, bool hasMore) {}
void TWS_Client::headTimestamp(int reqId, const std::string& headTimestamp) {}
void TWS_Client::histogramData(int reqId, const HistogramDataVector& data) {}
void TWS_Client::historicalDataUpdate(TickerId reqId, const Bar& bar) {}
void TWS_Client::rerouteMktDataReq(int reqId, int conid, const std::string& exchange) {}
void TWS_Client::rerouteMktDepthReq(int reqId, int conid, const std::string& exchange) {}
void TWS_Client::marketRule(int marketRuleId, const std::vector<PriceIncrement> &priceIncrements) {}
void TWS_Client::pnl(int reqId, double dailyPnL, double unrealizedPnL, double realizedPnL) {}
void TWS_Client::pnlSingle(int reqId, int pos, double dailyPnL, double unrealizedPnL, double realizedPnL, double value) {}
void TWS_Client::historicalTicks(int reqId, const std::vector<HistoricalTick> &ticks, bool done) {}
void TWS_Client::historicalTicksBidAsk(int reqId, const std::vector<HistoricalTickBidAsk> &ticks, bool done) {}
void TWS_Client::historicalTicksLast(int reqId, const std::vector<HistoricalTickLast> &ticks, bool done) {}
void TWS_Client::tickByTickAllLast(int reqId, int tickType, time_t time, double price, int size, const TickAttribLast& tickAttribLast, const std::string& exchange, const std::string& specialConditions) {}
void TWS_Client::tickByTickBidAsk(int reqId, time_t time, double bidPrice, double askPrice, int bidSize, int askSize, const TickAttribBidAsk& tickAttribBidAsk) {}
void TWS_Client::tickByTickMidPoint(int reqId, time_t time, double midPoint) {}
void TWS_Client::orderBound(long long orderId, int apiClientId, int apiOrderId) {}
void TWS_Client::completedOrder(const Contract& contract, const Order& order, const OrderState& orderState) {}
void TWS_Client::completedOrdersEnd() {}
void TWS_Client::replaceFAEnd(int reqId, const std::string& text) {}


