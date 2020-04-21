#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>
#include <netinet/in.h>
#include "server.h"

Server::Server(ServerHandler &handler, int port):port(port)
{
	int server_fd, new_socket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);

	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		throw "socket creation failed";
	}	

	if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		throw "setsockopt failed";
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		throw "bind failed";
	}

	listen(server_fd, 2);

	new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t*) &addrlen);
	threads.push_back(std::thread(Server::workerThread, new_socket, std::ref(handler)));
}

Server::~Server() 
{
	std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
		t.join();
	}); 

}

void Server::workerThread(int socket, ServerHandler &handler) 
{
	bool doPoll = true, doRead = true;
	int n = 0;
	std::stringbuf req = std::stringbuf();
	std::string resp;
	char buffer[READ_BUFFER_SIZE]; 
	struct pollfd poll_list[1];
	poll_list[0].fd = socket;
	poll_list[0].events = POLLIN|POLLPRI;

	while(doPoll) {
		//poll here and then set read to true when request pending
		n = poll(poll_list,1,0);
		doRead = true;
		while(doRead) {
			n = read(socket,buffer, READ_BUFFER_SIZE);	
			req.sputn(buffer,n-1);		
			doRead = (n == READ_BUFFER_SIZE);
		}
	        handler.handleRequest(req.str(), resp); 	

		//write response to socket
		n = send(socket, resp.c_str(), resp.length(), 0);
		if(n == -1) {
			throw "error writing to socket";
		}
	}
}

