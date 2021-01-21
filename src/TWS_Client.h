

#include "EWrapper.h"
#include "EReaderOSSignal.h"
#include "EReader.h"

#include <memory>
#include <vector>

class EClientSocket;


class TWS_Client : public EWrapper
{
public:

	TWS_Client();
	~TWS_Client();

	void setConnectOptions(const std::string&);
	void processMessages();

public:

	bool connect(const char * host, int port, int clientId = 0);
	void disconnect() const;
	bool isConnected() const;

private:

public:
	// events
	#include "EWrapper_prototypes.h"

private:
	//! [socket_declare]
	EReaderOSSignal m_osSignal;
	EClientSocket * m_pClient;
	//! [socket_declare]
	time_t m_sleepDeadline;

	OrderId m_orderId;
	std::unique_ptr<EReader> m_pReader;
    bool m_extraAuth;
	std::string m_bboExchange;
};
