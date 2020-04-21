#ifndef SERVER_H
#define SERVER_H

#include <stdlib.h>
#include <thread>
#include <vector>
#include "ServerHandler.h"

#define READ_BUFFER_SIZE 1024 

class Server {

private:
	int port = 8080;
	std::vector<std::thread> threads;
	
	static void workerThread(int socket, ServerHandler &handler);

public:
	//constructors
	Server(ServerHandler& handler, int port=8080);
	~Server();
	void operator=(Server const&);
	void run() throw();

};

#endif

