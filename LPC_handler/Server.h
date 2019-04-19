#pragma once
#pragma warning(disable:4996) 
#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include <string.h>
#include <Windows.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>	
#include "D:\ESIREM\C++\LPC\LPC\LPC\Socket_.h"
#include "Factory_Server.h"

struct st_Client
{
	SOCKET sock;
	std::string addr;
	unsigned int number;
	std::string city;
	std::string country;
	std::string ip_extern;
};

class Server : public Socket_
{
private:
	bool exit = 0;
	st_Client default_client;
	int port;
	std::vector<st_Client> clients;

public:
	
	Server(const int pPort);
	~Server();
	std::vector<st_Client> getClients();
	void setDefaultClient(st_Client _default);
	st_Client getDefaultClient() const;
	bool getExit();
	void setExit(const bool& pexit);
	bool acceptClient();
	void send_c();
	bool send_b(const char* pbuffer);
	bool send_b(const int &pbuffer);

	bool recv_b();
};
