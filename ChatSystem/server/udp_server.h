#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "comm.h"
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <map>
#include "data_pool.h"
#include <pthread.h>
#include "udp_data.h"

#define _IP_ "127.0.0.1"
#define _PORT_ 8080

class udp_server
{
public:
	void add_user(struct sockaddr_in &client);
	void old_user_del(struct sockaddr_in &client, std::string &in);

	udp_server(const std::string &_ip = _IP_, short  _port = _PORT_);	
	void init();
	ssize_t udp_recv(std::string &out);
	ssize_t udp_send(std::string &in, struct sockaddr_in &cli, socklen_t len);
	void broadcast();
	~udp_server();	

private:
	std::string ip;
	short port;
	int sock;
	data_pool pool;

	std::map<std::string, struct sockaddr_in > online_user;
};

void * recv_product(void *arg);

void * send_consum(void *arg);

