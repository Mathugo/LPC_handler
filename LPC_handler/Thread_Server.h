#pragma once
#include "Server.h"
#include "Scripts_s.h"
#include "Factory_Server.h"

void recv_t_old(Server* serv1);
void listen_client(Server* serv1, const unsigned short nb);
void accept_t(Server* serv1);
void send_t(Server* serv1);
