#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include <string>

class ServerHandler 
{
	public:
	virtual void handleRequest(std::string const &req, std::string &resp) = 0; 
};
#endif 
