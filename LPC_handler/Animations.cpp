#include "Animations.h"


void Animations::Welcome(const unsigned short& port)
{
	std::cout << "BOTNET Version : " << VERSION << std::endl;
	std::cout << "Last update : " << UPDATE << std::endl << std::endl;
	print_status("\t\t[ #--------------#	   Welcome to \t\t#------------#]");
	print_status("\t\t[ #--------------#       Le Petit Cheval        #------------#]");
	print_status("\t\t[ Fully undetectable payload.It allows you to do basic tricks ]");
	print_status("\t\t[ like screenshot, upload rootkit,custom exploit,enum password]");
	print_status("\t\t[ #--------------------MADE BY HUGO MATH---------------------#]");
	print_status("\t\t[ # Author:Hugo Math					     #]");
	print_status("\t\t[ # Script Developers : Hugo Math && Lucien Leseigle         #]");
	print_status("\t\t[ # Contributors      : Hugo Math && Lucien Leseigle         #]");
	print_warning("Enter : listen to start listenning to clients at the port : " + std::to_string(port));
	print_warning("Enter : exit to exit the handler");
	std::cout << ">> ";
}

void Animations::Start()
{
	system("cls");
	print_done("You have now access to the payload, be sure to check all options by taping : help");
}

void Animations::Loading(const int& pourcentage)
{
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
	std::cout << KBOLD << KRED << "[X] " << buffer << RST << std::endl;
}
void print_done(const std::string buffer)
{
	std::cout << KBOLD << KGRN << "[*] " << buffer << RST << std::endl;
}
void print_debug(const std::string buffer)
{
	std::cout << KBLU << "[*] " << buffer << RST << std::endl;
}

#endif
