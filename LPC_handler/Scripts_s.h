#pragma once
#include <iostream>
#include "Server.h"
#include <sstream>
#include <Lmcons.h>
#include "Animations.h"
#include <thread>
#include "Thread_Server.h"

#define BUFFER_LEN 256
void SetColor(int value);

class Server;

class Info

{	public:

	static void list_scripts();
	static void print_help();
	static bool set_session(Server* serv1, const std::string nb_session);
	static void list(Server* serv1);
	static void getsysinfo(Server* serv1);
	static void version(Server* serv1);
	static void getcurrentsession(Server* serv1);

};
class Transfer
{
public:
	static void uploadToClient(Server* serv1, const std::string filename);
	static int getSize(std::string filename);

};