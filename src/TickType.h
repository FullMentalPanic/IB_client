/*
Tick type define https://interactivebrokers.github.io/tws-api/tick_types.html
*/

#define	BID_SIZE	0	//	Number of contracts or lots offered at the bid price.	IBApi.EWrapper.tickSize	-
#define	BID_PRICE	1	//	Highest priced bid for the contract.	IBApi.EWrapper.tickPrice	-
#define	ASK_PRICE	2	//	Lowest price offer on the contract.	IBApi.EWrapper.tickPrice	-
#define	ASK_SIZE	3	//	Number of contracts or lots offered at the ask price.	IBApi.EWrapper.tickSize	-
#define	LAST_PRICE	4	//	Last price at which the contract traded (does not include some trades in RTVolume).	IBApi.EWrapper.tickPrice	-
#define	LAST_SIZE	5	//	Number of contracts or lots traded at the last price.	IBApi.EWrapper.tickSize	-
#define	HIGH	6	//	High price for the day.	IBApi.EWrapper.tickPrice	-
#define	LOW	7	//	Low price for the day.	IBApi.EWrapper.tickPrice	-
#define	VOLUME	8	//	Trading volume for the day for the selected contract (US Stocks: multiplier 100).	IBApi.EWrapper.tickSize	-
#define	CLOSE_PRICE	9	//	The last available closing price for the previous day. For US Equities, we use corporate action processing to get the closing price, so the close price is adjusted to reflect forward and reverse splits and cash and stock dividends.	IBApi.EWrapper.tickPrice	-
#define	BID_OPTION_COMPUTATION	10	//	Computed Greeks and implied volatility based on the underlying stock price and the option bid price. See Option Greeks	IBApi.EWrapper.tickOptionComputation	-
#define	ASK_OPTION_COMPUTATION	11	//	Computed Greeks and implied volatility based on the underlying stock price and the option ask price. See Option Greeks	IBApi.EWrapper.tickOptionComputation	-
#define	LAST_OPTION_COMPUTATION	12	//	Computed Greeks and implied volatility based on the underlying stock price and the option last traded price. See Option Greeks	IBApi.EWrapper.tickOptionComputation	-
#define	MODEL_OPTION_COMPUTATION	13	//	Computed Greeks and implied volatility based on the underlying stock price and the option model price. Correspond to greeks shown in TWS. See Option Greeks	IBApi.EWrapper.tickOptionComputation	-
#define	OPEN_TICK	14	//	Current session's opening price. Before open will refer to previous day. The official opening price requires a market data subscription to the native exchange of the instrument.	IBApi.EWrapper.tickPrice	-
#define	LOW_13_WEEKS	15	//	Lowest price for the last 13 weeks. For stocks only.	IBApi.EWrapper.tickPrice	165
#define	HIGH_13_WEEKS	16	//	Highest price for the last 13 weeks. For stocks only.	IBApi.EWrapper.tickPrice	165
#define	LOW_26_WEEKS	17	//	Lowest price for the last 26 weeks. For stocks only.	IBApi.EWrapper.tickPrice	165
#define	HIGH_26_WEEKS	18	//	Highest price for the last 26 weeks. For stocks only.	IBApi.EWrapper.tickPrice	165
#define	LOW_52_WEEKS	19	//	Lowest price for the last 52 weeks. For stocks only.	IBApi.EWrapper.tickPrice	165
#define	HIGH_52_WEEKS	20	//	Highest price for the last 52 weeks. For stocks only.	IBApi.EWrapper.tickPrice	165
#define	AVERAGE_VOLUME	21	//	The average daily trading volume over 90 days. Multiplier of 100. For stocks only.	IBApi.EWrapper.tickSize	165
#define	OPEN_INTEREST	22	//	(Deprecated, not currently in use) Total number of options that are not closed.	IBApi.EWrapper.tickSize	-
#define	OPTION_HISTORICAL_VOLATILITY	23	//	The 30-day historical volatility (currently for stocks).	IBApi.EWrapper.tickGeneric	104
#define	OPTION_IMPLIED_VOLATILITY	24	//	A prediction of how volatile an underlying will be in the future. The IB 30-day volatility is the at-market volatility estimated for a maturity thirty calendar days forward of the current trading day, and is based on option prices from two consecutive expiration months.	IBApi.EWrapper.tickGeneric	106
#define	OPTION_BID_EXCHANGE	25	//	Not Used.	IBApi.EWrapper.tickString	-
#define	OPTION_ASK_EXCHANGE	26	//	Not Used.	IBApi.EWrapper.tickString	-
#define	OPTION_CALL_OPEN_INTEREST	27	//	Call option open interest.	IBApi.EWrapper.tickSize	101
#define	OPTION_PUT_OPEN_INTEREST	28	//	Put option open interest.	IBApi.EWrapper.tickSize	101
#define	OPTION_CALL_VOLUME	29	//	Call option volume for the trading day.	IBApi.EWrapper.tickSize	100
#define	OPTION_PUT_VOLUME	30	//	Put option volume for the trading day.	IBApi.EWrapper.tickSize	100
#define	INDEX_FUTURE_PREMIUM	31	//	The number of points that the index is over the cash index.	IBApi.EWrapper.tickGeneric	162
#define	BID_EXCHANGE	32	//	For stock and options, identifies the exchange(s) posting the bid price. See Component Exchanges	IBApi.EWrapper.tickString	-
#define	ASK_EXCHANGE	33	//	For stock and options, identifies the exchange(s) posting the ask price. See Component Exchanges	IBApi.EWrapper.tickString	-
#define	AUCTION_VOLUME	34	//	The number of shares that would trade if no new orders were received and the auction were held now.	IBApi.EWrapper.tickSize	225
#define	AUCTION_PRICE	35	//	The price at which the auction would occur if no new orders were received and the auction were held now- the indicative price for the auction. Typically received after Auction imbalance (tick type 36)	IBApi.EWrapper.tickPrice	225
#define	AUCTION_IMBALANCE	36	//	The number of unmatched shares for the next auction; returns how many more shares are on one side of the auction than the other. Typically received after Auction Volume (tick type 34)	IBApi.EWrapper.tickSize	225
#define	MARK_PRICE	37	//	The mark price is the current theoretical calculated value of an instrument. Since it is a calculated value, it will typically have many digits of precision.	IBApi.EWrapper.tickPrice	232
#define	BID_EFP_COMPUTATION	38	//	Computed EFP bid price	IBApi.EWrapper.tickEFP	-
#define	ASK_EFP_COMPUTATION	39	//	Computed EFP ask price	IBApi.EWrapper.tickEFP	-
#define	LAST_EFP_COMPUTATION	40	//	Computed EFP last price	IBApi.EWrapper.tickEFP	-
#define	OPEN_EFP_COMPUTATION	41	//	Computed EFP open price	IBApi.EWrapper.tickEFP	-
#define	HIGH_EFP_COMPUTATION	42	//	Computed high EFP traded price for the day	IBApi.EWrapper.tickEFP	-
#define	LOW_EFP_COMPUTATION	43	//	Computed low EFP traded price for the day	IBApi.EWrapper.tickEFP	-
#define	CLOSE_EFP_COMPUTATION	44	//	Computed closing EFP price for previous day	IBApi.EWrapper.tickEFP	-
#define	LAST_TIMESTAMP	45	//	Time of the last trade (in UNIX time).	IBApi.EWrapper.tickString	-
#define	SHORTABLE	46	//	Describes the level of difficulty with which the contract can be sold short. See Shortable	IBApi.EWrapper.tickGeneric	236
#define	RT_VOLUME_TIME_SALES	48	//	Last trade details (Including both "Last" and "Unreportable Last" trades). See RT Volume	IBApi.EWrapper.tickString	233
#define	HALTED	49	//	Indicates if a contract is halted. See Halted	IBApi.EWrapper.tickGeneric	-
#define	BID_YIELD	50	//	Implied yield of the bond if it is purchased at the current bid.	IBApi.EWrapper.tickPrice	-
#define	ASK_YIELD	51	//	Implied yield of the bond if it is purchased at the current ask.	IBApi.EWrapper.tickPrice	-
#define	LAST_YIELD	52	//	Implied yield of the bond if it is purchased at the last price.	IBApi.EWrapper.tickPrice	-
#define	CUSTOM_OPTION_COMPUTATION	53	//	Greek values are based off a user customized price.	IBApi.EWrapper.tickOptionComputation	-
#define	TRADE_COUNT	54	//	Trade count for the day.	IBApi.EWrapper.tickGeneric	293
#define	TRADE_RATE	55	//	Trade count per minute.	IBApi.EWrapper.tickGeneric	294
#define	VOLUME_RATE	56	//	Volume per minute.	IBApi.EWrapper.tickGeneric	295
#define	LAST_RTH_TRADE	57	//	Last Regular Trading Hours traded price.	IBApi.EWrapper.tickPrice	318
#define	RT_HISTORICAL_VOLATILITY	58	//	30-day real time historical volatility.	IBApi.EWrapper.tickGeneric	411
#define	IB_DIVIDENDS	59	//	Contract's dividends. See IB Dividends.	IBApi.EWrapper.tickString	456
#define	BOND_FACTOR_MULTIPLIER	60	//	The bond factor is a number that indicates the ratio of the current bond principal to the original principal	IBApi.EWrapper.tickGeneric	460
#define	REGULATORY_IMBALANCE	61	//	The imbalance that is used to determine which at-the-open or at-the-close orders can be entered following the publishing of the regulatory imbalance.	IBApi.EWrapper.tickSize	225
#define	NEWS	62	//	Contract's news feed.	IBApi.EWrapper.tickString	292
#define	SHORT_TERM_VOLUME_3_MINUTES	63	//	The past three minutes volume. Interpolation may be applied. For stocks only.	IBApi.EWrapper.tickSize	595
#define	SHORT_TERM_VOLUME_5_MINUTES	64	//	The past five minutes volume. Interpolation may be applied. For stocks only.	IBApi.EWrapper.tickSize	595
#define	SHORT_TERM_VOLUME_10_MINUTES	65	//	The past ten minutes volume. Interpolation may be applied. For stocks only.	IBApi.EWrapper.tickSize	595
#define	DELAYED_BID	66	//	Delayed bid price. See Market Data Types.	IBApi.EWrapper.tickPrice	-
#define	DELAYED_ASK	67	//	Delayed ask price. See Market Data Types.	IBApi.EWrapper.tickPrice	-
#define	DELAYED_LAST	68	//	Delayed last traded price. See Market Data Types.	IBApi.EWrapper.tickPrice	-
#define	DELAYED_BID_SIZE	69	//	Delayed bid size. See Market Data Types.	IBApi.EWrapper.tickSize	-
#define	DELAYED_ASK_SIZE	70	//	Delayed ask size. See Market Data Types.	IBApi.EWrapper.tickSize	-
#define	DELAYED_LAST_SIZE	71	//	Delayed last size. See Market Data Types.	IBApi.EWrapper.tickSize	-
#define	DELAYED_HIGH_PRICE	72	//	Delayed highest price of the day. See Market Data Types.	IBApi.EWrapper.tickPrice	-
#define	DELAYED_LOW_PRICE	73	//	Delayed lowest price of the day. See Market Data Types	IBApi.EWrapper.tickPrice	-
#define	DELAYED_VOLUME	74	//	Delayed traded volume of the day. See Market Data Types	IBApi.EWrapper.tickSize	-
#define	DELAYED_CLOSE	75	//	The prior day's closing price.	IBApi.EWrapper.tickPrice	-
#define	DELAYED_OPEN	76	//	Not currently available	IBApi.EWrapper.tickPrice	-
#define	RT_TRADE_VOLUME	77	//	Last trade details that excludes "Unreportable Trades". See RT Trade Volume	IBApi.EWrapper.tickString	375
#define	CREDITMAN_MARK_PRICE	78	//	Not currently available	IBApi.EWrapper.tickPrice	
#define	CREDITMAN_SLOW_MARK_PRICE	79	//	Slower mark price update used in system calculations	IBApi.EWrapper.tickPrice	619
#define	DELAYED_BID_OPTION	80	//	Computed greeks based on delayed bid price. See Market Data Types and Option Greeks.	IBApi.EWrapper.tickPrice	
#define	DELAYED_ASK_OPTION	81	//	Computed greeks based on delayed ask price. See Market Data Types and Option Greeks.	IBApi.EWrapper.tickPrice	
#define	DELAYED_LAST_OPTION	82	//	Computed greeks based on delayed last price. See Market Data Types and Option Greeks.	IBApi.EWrapper.tickPrice	
#define	DELAYED_MODEL_OPTION	83	//	Computed Greeks and model's implied volatility based on delayed stock and option prices.	IBApi.EWrapper.tickPrice	
#define	LAST_EXCHANGE	84	//	Exchange of last traded price	IBApi.EWrapper.tickString	
#define	LAST_REGULATORY_TIME	85	//	Timestamp (in Unix ms time) of last trade returned with regulatory snapshot	IBApi.EWrapper.tickString	
#define	FUTURES_OPEN_INTEREST	86	//	Total number of outstanding futures contracts (TWS v965+). *HSI open interest requested with generic tick 101	IBApi.EWrapper.tickSize	588
#define	AVERAGE_OPTION_VOLUME	87	//	Average volume of the corresponding option contracts(TWS Build 970+ is required)	IBApi.EWrapper.tickSize	105
#define	DELAYED_LAST_TIMESTAMP	88	//	Delayed time of the last trade (in UNIX time) (TWS Build 970+ is required)	IBApi.EWrapper.tickString	
#define	SHORTABLE_SHARES	89	//	Number of shares available to short (TWS Build 974+ is required)	IBApi.EWrapper.tickSize	236
#define	ETF_NAV_CLOSE	92	//	Today's closing price of ETF's Net Asset Value (NAV). Calculation is based on prices of ETF's underlying securities.	IBApi.EWrapper.tickPrice	578
#define	ETF_NAV_PRIOR_CLOSE	93	//	Yesterday's closing price of ETF's Net Asset Value (NAV). Calculation is based on prices of ETF's underlying securities.	IBApi.EWrapper.tickPrice	578
#define	ETF_NAV_BID	94	//	The bid price of ETF's Net Asset Value (NAV). Calculation is based on prices of ETF's underlying securities.	IBApi.EWrapper.tickPrice	576
#define	ETF_NAV_ASK	95	//	The ask price of ETF's Net Asset Value (NAV). Calculation is based on prices of ETF's underlying securities.	IBApi.EWrapper.tickPrice	576
#define	ETF_NAV_LAST	96	//	The last price of Net Asset Value (NAV). For ETFs: Calculation is based on prices of ETF's underlying securities. For NextShares: Value is provided by NASDAQ	IBApi.EWrapper.tickPrice	577
#define	ETF_NAV_FROZEN_LAST	97	//	ETF Nav Last for Frozen data	IBApi.EWrapper.tickPrice	623
#define	ETF_NAV_HIGH	98	//	The high price of ETF's Net Asset Value (NAV)	IBApi.EWrapper.tickPrice	614
#define	ETF_NAV_LOW	99	//	The low price of ETF's Net Asset Value (NAV)	IBApi.EWrapper.tickPrice	614
