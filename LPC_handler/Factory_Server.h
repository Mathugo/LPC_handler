#pragma once
#include <vector>
#include "Server.h"
#include "Scripts_s.h"

class Server;

class Factory_Server
{
private:
	std::vector<std::string> args;
	const std::string buffer;
public:
	Factory_Server(Server* sock, const char* pbuffer);

};

std::vector<std::string> split(const char* buffer);