# LPC_handler
Handler of the C++ Projet LPC

## Getting Started
These instructions will get you a copy of the project up and running on your local machine

### Prerequisites

It's recommended to use the handler on a linux machine, so you can easily access 
to the handler by using SSH, but you can build this project with Visual Studio.


### Installing and building
You will need to have github on your local machine
Before building the project, you need to indicate what PORT the handler will be listen to in the main() function : 
[LPC_handler](https://github.com/Mathugo/LPC_handler/blob/master/LPC_handler/LPC_handler.cpp). [!] Any PORT > 32768 will not work
```
int main(int argc, char *argv[])
{

	const unsigned short port = YOUR_PORT //
  .
  .
  .
 }
 ```
### Windows :
Just clone the github repo and build the project with Visual Studio or with g++, example : 
```
g++ all_your_cpp_files -o handler -std=c++11
```
Then execute it. It is important that you put all your files you want to upload in the futur on the Zombies, in the same directory as the executable

## #Linux :
Just clone the gitjub repo and build the project : 
```
git init
git clone https://github.com/Mathugo/LPC_handler.git
cd LPC_handler
chmod +x RUN.sh 
./RUN.sh
```

## Running the tests 
No tests are plannified for the moments

## Contributors
* **Lucien Leseigle**

## Authors 
* **Hugo Math**

