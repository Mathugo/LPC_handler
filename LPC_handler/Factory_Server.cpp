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
	SetColor(12);
	std::cout << "[*] Error while sending buffer to the current client :" << serv1->getDefaultClient().ip_extern << std::endl;
	std::cout << "[*] The client " << serv1->getDefaultClient().ip_extern << " might be deconnected" << std::endl;
	SetColor(4);
	std::cout << "[*] Removing .." << std::endl;
	if (serv1->getClients().size() == 1)
	{
		std::cout << "[*] No other active sessions --> shutting down the handler ..." << std::endl;
		SetColor(7);
		exit(1);
	}
	else
	{
		SetColor(7);
		serv1->removeDefaultClient();
	}

}

Factory_Server::Factory_Server(Server* serv1,const char* pbuffer) : buffer(pbuffer)
{
	args = split(pbuffer);

	if (args[0] == "exit" ||args[0] == "EXIT")
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
		Info::set_session(serv1,args[1]);
	}
	else if (args[0] == "getcurrentsession" && args.size() == 1)
	{
		Info::getcurrentsession(serv1);
	}
	else if (args[0] == "list_scripts")
	{
		Info::list_scripts();
	}
	else
	{
		if (serv1->send_b(buffer.c_str()))	{remove_client(serv1);}
	}
}

