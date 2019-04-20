#pragma once
#include "scripts_s.h"
#include <iostream>
#define VERSION "1.1"
#define UPDATE "update function()"
class Animations
{
public:
	static void Welcome(const unsigned short& port);
	static void Start();
	static void Loading(const int &pourcentage);

};

 void print_status(const std::string buffer);
void print_warning(const std::string buffer);
void print_done(const std::string buffer);
void print_debug(const std::string buffer);