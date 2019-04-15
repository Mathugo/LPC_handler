#pragma once
#include <iostream>
#include "Server.h"
#include <sstream>
#include <Lmcons.h>

#define BUFFER_LEN 256
void SetColor(int value);


class Server;

class Info

{	public:

	static void list_scripts();
	static void print_help();
	static bool set_session(Server* serv1);
	static void list(Server* serv1);
	static void getsysinfo(Server* serv1);

};
class Transfer
{
public:
	static void uploadToClient(Server* serv1, const std::string filename);
};