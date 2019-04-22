#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "Server.h"
#pragma comment(lib, "Ws2_32.lib")
#include <vector>
#include <thread>
#include <Windows.h>
#include "Animations.h"
#include "Thread_Server.h"


int main(int argc, char *argv[])
{

	const unsigned short port = 9997;
	std::string enter;

	while (enter != "listen")
	{
		Animations::Welcome(port);
		std::cin >> enter;
		system("cls");
		if (enter == "exit") { return 0; }

	}

	std::vector<std::thread> thread_list;

	Server* serv1 = new Server(port);
	
	bool test = 0;
	int nb = 0;

	serv1->acceptClient();
	thread_list.push_back(std::thread(listen_client, serv1, nb));
	nb++;
	
	std::thread t_send(send_t, serv1);
	
	Sleep(3000);
	Animations::Start();
	
	while (serv1->getError() != 1 || serv1->getExit() != 1)
	{
		test = serv1->acceptClient();
		if (test)
		{
			thread_list.push_back(std::thread(listen_client, serv1, nb));
			nb++;
		}
		Sleep(500);
	}

	print_warning("Closing threads ..");
	delete serv1;
	t_send.join();
	for (int i = 0; i < thread_list.size(); i++)
	{
		thread_list[i].join();
	}
	print_done("Done");
}
