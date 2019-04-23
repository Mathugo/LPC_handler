#include <iostream>

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

#include "Socket_.h"
#include "Server.h"
#include <vector>
#include <thread>
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
	
//	Sleep(3000);
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));

	Animations::Start();
	
	while (serv1->getError() != 1 || serv1->getExit() != 1)
	{
		test = serv1->acceptClient();
		if (test)
		{
			thread_list.push_back(std::thread(listen_client, serv1, nb));
			nb++;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		//Sleep(500);
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
