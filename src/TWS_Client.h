

#include "EWrapper.h"
#include "EReaderOSSignal.h"
#include "EReader.h"

#include <memory>
#include <vector>
#include <boost/thread.hpp>

class EClientSocket;


class TWS_Client : public EWrapper
{
public:

	TWS_Client();
	~TWS_Client();

	void setConnectOptions(const std::string&);
	bool connect(const char * host, int port, int clientId = 0);
	void disconnect();
	bool isConnected();
	void accountOperations();

private:
	void run();
public:
	// events
	#include "EWrapper_prototypes.h"

private:
	//! [socket_declare]
	EReaderOSSignal m_osSignal;
	EClientSocket * m_pClient;
	boost::thread *worker;
	//! [socket_declare]
	time_t m_sleepDeadline;

	OrderId m_orderId;
	std::unique_ptr<EReader> m_pReader;
    bool m_extraAuth;
	//std::string m_bboExchange;
};
