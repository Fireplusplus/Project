#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

#include "comm.h"
#include "protocol.h"
#include "transfer.h"

using namespace std;

int proc_transfer(int in, const char *ip, const char *port);

static void usage(char *arg)
{
	cout << "Usage " << arg << "[port] [peer_ip] [peer_port]" << endl;
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		usage(argv[0]);
		exit(1);
	}

	int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock < 0)
	{
		perror("listen");
		exit(2);
	}
	sockaddr_in local;
	memset(&local, 0, sizeof(local));
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(atoi(argv[1]));
	if (bind(listen_sock, (sockaddr *)&local, sizeof(local)) < 0)
	{
		perror("bind");
		exit(3);
	}
	if (listen(listen_sock, 5) < 0)
	{
		perror("listen");
		exit(4);
	}

	while (true)
	{
		sockaddr_in cli_addr;
		socklen_t len = sizeof(cli_addr);
		int in = accept(listen_sock, (sockaddr *)&cli_addr, &len);
		if (in < 0)
		{
			perror("accept");
			continue;
		}

		pid_t id1 = fork();
		if (id1 < 0)
		{
			perror("fork");
			continue;
		}
		else if (id1 > 0)	// father
		{
			waitpid(id1, NULL, 0);
			close(in);
		}
		else		// child
		{
			pid_t id2 = fork();
			if (id2 < 0)
			{
				exit(5);	
			}
			if (id2 > 0)	//father
			{
				exit(0);
			}
			else
			{
				close(listen_sock);	
				return proc_transfer(in, argv[2], argv[3]);
			}
		}
		
	}


	return 0;
}


int proc_transfer(int in, const char *ip, const char *port)
{
	int out = socket(AF_INET, SOCK_STREAM, 0);
	if (out < 0)
	{
		perror("socket");
		return 6;
	}
	
	sockaddr_in ser_addr;
	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = inet_addr(ip);
	ser_addr.sin_port = htons(atoi(port));

	if (connect(out, (sockaddr *)&ser_addr, sizeof(ser_addr)) < 0)
	{
		perror("connect");
		return 7;
	}
	
	Param up = {in, out, 0};
	Param down = {out, in, 0};
	
	pthread_create(&up.bro, NULL, transfer, &up);
	pthread_create(&down.bro, NULL, transfer, &down);

	pthread_join(up.bro, NULL);
	pthread_join(down.bro, NULL);
	return 0;
}


