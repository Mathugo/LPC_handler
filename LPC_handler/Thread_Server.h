#pragma once
#include "Server.h"
#include "Scripts_s.h"
#include "Factory_Server.h"
#define REFRESH_RECV 100
#define HUGE_BUFFER 16384
#include <chrono>
#include <thread>

class Server;
void recv_t_old(Server* serv1);
void listen_client(Server* serv1, const unsigned short nb);
void accept_t(Server* serv1);
void send_t(Server* serv1);
void refresh(bool* done, const unsigned int& refresh_rate, const int* pourcentage);

