#include "Animations.h"


void Animations::Welcome(const unsigned short& port)
{
	std::cout << "BOTNET Version : " << VERSION << std::endl;
	std::cout << "Last update : " << UPDATE << std::endl << std::endl;
	SetColor(6);

	std::cout <<"\t\t[ #--------------#	   Welcome to \t\t#------------#]" << std::endl;
	std::cout <<"\t\t[ #--------------#       Le Petit Cheval        #------------#]" << std::endl;
	std::cout <<"\t\t[ Fully undetectable payload.It allows you to do basic tricks ]" << std::endl;
	std::cout <<"\t\t[ like screenshot, upload rootkit,custom exploit,enum password]" << std::endl;
	std::cout <<"\t\t[ #--------------------MADE BY HUGO MATH---------------------#]" << std::endl;
	std::cout <<"\t\t[ # Author            : Hugo Math                            #]" << std::endl;
	std::cout <<"\t\t[ # Script Developers : Hugo Math && Lucien Leseigle         #]" << std::endl;
	std::cout <<"\t\t[ # Contributors      : Hugo Math && Lucien Leseigle         #]" << std::endl;
	std::cout <<"[*] WARNING this handler only works on Windows" << std::endl << std::endl;
	SetColor(14);
	std::cout << "Enter : listen to start listenning to clients at the port : " << port<< std::endl;
	std::cout << "Enter : exit to exit the handler" << std::endl;
	SetColor(7);
	std::cout << ">> ";
}

void Animations::Start()
{
	system("cls");
	SetColor(2);
	std::cout << "[*] You have now access to the payload, be sure to check all options by taping : help" << std::endl;
	SetColor(7);
}

void Animations::Loading(const int& pourcentage)
{
		SetColor(6);
		print_status("Please wait until the file is transfered ..");
		print_status(std::to_string(pourcentage) + "%");
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

#ifdef _WIN32

void print_status(const std::string buffer)
{
	SetColor(6);
	std::cout << "[*] " << buffer << std::endl;
	SetColor(7);
}

void print_warning(const std::string buffer)
{
	SetColor(14);
	std::cout << "[!] " << buffer << std::endl;
	SetColor(7);
}
void print_error(const std::string buffer)
{
	SetColor(12);
	std::cout << "[X] " << buffer << std::endl;
	SetColor(7);
}
void print_done(const std::string buffer)
{
	SetColor(2);
	std::cout << "[*] " << buffer << std::endl;
	SetColor(7);
}
void print_debug(const std::string buffer)
{
	SetColor(1);
	std::cout << "[*] " << buffer << std::endl;
	SetColor(7);
}
#else


#ifndef _COLORS_
#define _COLORS_

#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define KBOLD "\x1B[1m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

#endif 

void print_status(const std::string buffer)
{
	std::cout << KYEL << "[*] " << buffer << RST << std::endl;
}

void print_warning(const std::string buffer)
{
	std::cout << KYEL << "[!] " << buffer << RST << std::endl;
}
void print_error(const std::string buffer)
{
	std::cout << KBOLD << FRED << "[X] " << buffer << RST << std::endl;
}
void print_done(const std::string buffer)
{
	std::cout << KBOLD << FGRN << "[*] " << buffer << RST << std::endl;
}
void print_debug(const std::string buffer)
{
	std::cout << KBLU << "[*] " << buffer << RST << std::endl;
}

#endif
