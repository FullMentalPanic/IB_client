#include "TWS_Client.h"


#include <thread>

const unsigned MAX_ATTEMPTS = 50;
const unsigned SLEEP_TIME = 10;

int main(int argc, char** argv)
{
	const char* host = argc > 1 ? argv[1] : "";
	int port = argc > 2 ? atoi(argv[2]) : 0;
	if (port <= 0)
		port = 7496;
	const char* connectOptions = argc > 3 ? argv[3] : "";
	int clientId = 0;

	unsigned attempt = 0;
	
	printf( "Start of C++ Socket Client Test %u\n", attempt);


	while( attempt < MAX_ATTEMPTS){
		++attempt;
		printf( "Attempt %u of %u\n", attempt, MAX_ATTEMPTS);
		TWS_Client client;
		try{
			client.connect( host, port, clientId);
			while(1){
				std::this_thread::sleep_for(std::chrono::seconds(SLEEP_TIME));
			}
		}catch(int error){
			printf( "Sleeping %u seconds before next attempt\n", SLEEP_TIME);
			std::this_thread::sleep_for(std::chrono::seconds(SLEEP_TIME));
		}
	}

	printf ( "End of C++ Socket Client Test\n");
}

