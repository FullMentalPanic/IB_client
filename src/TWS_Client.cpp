#include "TWS_Client.h"
#include "EClientSocket.h"


TWS_Client::TWS_Client(){
    m_osSignal = EReaderOSSignal(2000);
    m_pClient  = new EClientSocket(this, &m_osSignal);
    m_orderId = 0;
}

TWS_Client::~TWS_Client(){
	if( m_pReader )
		m_pReader.reset();

	delete m_pClient;
}

bool TWS_Client::connect(const char * host, int port, int clientId = 0 ){	
	bool bRes = m_pClient->eConnect( host, port, clientId, m_extraAuth);
	
	if (bRes) {
		printf( "Connected to %s:%d clientId:%d\n", m_pClient->host().c_str(), m_pClient->port(), clientId);
		m_pReader = std::unique_ptr<EReader>( new EReader(m_pClient, &m_osSignal) );
		m_pReader->start();

		

	}
	else
		printf( "Cannot connect to %s:%d clientId:%d\n", m_pClient->host().c_str(), m_pClient->port(), clientId);

	return bRes;
}

void TWS_Client::disconnect(){

}
bool TWS_Client::isConnected(){

}

void TWS_Client::tickPrice( TickerId tickerId, TickType field, double price, const TickAttrib& attrib) {}
void TWS_Client::tickSize( TickerId tickerId, TickType field, int size) {}
void TWS_Client::tickOptionComputation( TickerId tickerId, TickType tickType, int tickAttrib, double impliedVol, double delta,
	double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice) {}
void TWS_Client::tickGeneric(TickerId tickerId, TickType tickType, double value) {}
void TWS_Client::tickString(TickerId tickerId, TickType tickType, const std::string& value) {}
void TWS_Client::tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const std::string& formattedBasisPoints,
	double totalDividends, int holdDays, const std::string& futureLastTradeDate, double dividendImpact, double dividendsToLastTradeDate) {}
void TWS_Client::orderStatus( OrderId orderId, const std::string& status, double filled,
	double remaining, double avgFillPrice, int permId, int parentId,
	double lastFillPrice, int clientId, const std::string& whyHeld, double mktCapPrice) {}
void TWS_Client::openOrder( OrderId orderId, const Contract&, const Order&, const OrderState&) {}
void TWS_Client::openOrderEnd() {}
void TWS_Client::winError( const std::string& str, int lastError) {}
void TWS_Client::connectionClosed() {}
void TWS_Client::updateAccountValue(const std::string& key, const std::string& val,
const std::string& currency, const std::string& accountName) {}
void TWS_Client::updatePortfolio( const Contract& contract, double position,
	double marketPrice, double marketValue, double averageCost,
	double unrealizedPNL, double realizedPNL, const std::string& accountName) {}
void TWS_Client::updateAccountTime(const std::string& timeStamp) {}
void TWS_Client::accountDownloadEnd(const std::string& accountName) {}
void TWS_Client::nextValidId( OrderId orderId) {}
void TWS_Client::contractDetails( int reqId, const ContractDetails& contractDetails) {}
void TWS_Client::bondContractDetails( int reqId, const ContractDetails& contractDetails) {}
void TWS_Client::contractDetailsEnd( int reqId) {}
void TWS_Client::execDetails( int reqId, const Contract& contract, const Execution& execution) {}
void TWS_Client::execDetailsEnd( int reqId) {}
void TWS_Client::error(int id, int errorCode, const std::string& errorString) {}
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
void TWS_Client::accountSummary( int reqId, const std::string& account, const std::string& tag, const std::string& value, const std::string& curency) {}
void TWS_Client::accountSummaryEnd( int reqId) {}
void TWS_Client::verifyMessageAPI( const std::string& apiData) {}
void TWS_Client::verifyCompleted( bool isSuccessful, const std::string& errorText) {}
void TWS_Client::displayGroupList( int reqId, const std::string& groups) {}
void TWS_Client::displayGroupUpdated( int reqId, const std::string& contractInfo) {}
void TWS_Client::verifyAndAuthMessageAPI( const std::string& apiData, const std::string& xyzChallange) {}
void TWS_Client::verifyAndAuthCompleted( bool isSuccessful, const std::string& errorText) {}
void TWS_Client::connectAck() {}
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