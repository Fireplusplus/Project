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
#include "udp_data.h"
#include <vector>
#include <semaphore.h>
#include <strstream>
#include <algorithm>

class udp_client
{
public:
	udp_client(const std::string &_remote_ip = "127.0.0.1", short _remote_port = 8080);
	
	void init();
	
	void add_flist(std::string &user);

	ssize_t udp_recv(std::string &out);
	ssize_t udp_send(std::string &in, struct sockaddr_in &ser, socklen_t &len);
	
	~udp_client();

public:
	std::vector<std::string> flist;
	sem_t lock;
private:
	int sock;
	std::string remote_ip;	
	short remote_port;
};
