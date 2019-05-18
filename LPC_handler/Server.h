#pragma once
#pragma warning(disable:4996) 

#ifdef _WIN32
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#endif

#include <iostream>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>	
#include "Socket_.h"
#include "Factory_Server.h"
#include "Animations.h"

struct st_Client
{
	SOCKET sock;
	std::string addr="0.0.0.0";
	unsigned short sin_port = 0;
	unsigned int number=0;
	std::string city="None";
	std::string country="None";
	std::string ip_extern="0.0.0.0";
	bool mute = 0;
};

class Server : public Socket_
{
private:
	bool exit_ = 0;
	st_Client default_client;
	int port;
	std::vector<st_Client> clients;

public:
	
	Server(const int pPort);
	~Server();
	std::vector<st_Client>& getClients();
	void setDefaultClient(st_Client& _default);
	st_Client& getDefaultClient();
	st_Client& getClient(const unsigned short& nb);
	void setMute(const unsigned short& nb);
	void setUnmute(const unsigned short& nb);
	SOCKET& getSockCl(const unsigned short& nb);
	void removeDefaultClient();
	void removeClient(const unsigned short& nb);
	bool getExit();
	void setExit(const bool& pexit);
	void shutdown();
	bool acceptClient();
	void send_c();
	bool send_b(const char* pbuffer);
	bool send_b(const int &pbuffer);

	bool recv_b();
};
