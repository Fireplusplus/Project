#include <iostream>
#include <sys/types.h>          
#include <sys/socket.h>
#include <assert.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>

#include "comm.h"
#include "protocol.h"
#include "transfer.h"


using namespace std;

int proc_socks(int in);

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		cout << "Usage ./ser [port]" << endl;
		exit(1);
	}

	int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock < 0)
	{
		perror("socket");
		exit(2);
	}

	sockaddr_in ser_addr;
	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(atoi(argv[1]));	
	ser_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(listen_sock, (sockaddr *)&ser_addr, sizeof(ser_addr)) < 0)
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
		// 获取客户端地址
		sockaddr_in cli_addr;
		socklen_t len = sizeof(cli_addr);
		int in = accept(listen_sock, (sockaddr *)&cli_addr, &len);
		if (in < 0)
		{
			perror("accept");	
			continue;
		}
		
		// 两次fork，使孙子进程称为孤儿
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
		else 		// child
		{
			pid_t id2 = fork();
			if (id2 < 0)
			{
				perror("fork");
				exit(5);
			}
			else if (id2 > 0)	// father
			{
				exit(0);
			}
			else		// child
			{
				close(listen_sock);	
				return proc_socks(in);
			}
		}
	}
		
}

int proc_socks(int in)
{
	// 接收客户端验证请求
	SKReq sreq;
	recv_n(in, (char *)&sreq, sizeof(sreq));

	if (sreq.ver != 5 || sreq.n != 1)
	{
		cout << "protocol error" << endl;
		return 6;
	}
	char methods[8];	
	recv_n(in, methods, sreq.n);
	if (0 != methods[0])
	{
		cout << "methods error" << endl;
		return 7;
	}

	// 服务器回应
	SKRep srep;
	srep.ver = 5;	// SOCK5
	srep.m = 0;	// 无验证
	send_n(in, (char *)&srep, sizeof(srep));

	sockaddr_in out_addr;
	memset(&out_addr, 0, sizeof(out_addr));
	out_addr.sin_family = AF_INET;

	// 接收客户端具体请求
	AddrReq areq;
	recv_n(in, (char *)&areq, sizeof(areq));
	if (areq.ver != 5 || areq.cmd != 1 || areq.rsv != 0)
	{
		cout << "protocol error" << endl;
		return 8;
	}
	if (areq.atype == 1)
	{
		// ipv4
		recv_n(in, (char *)&out_addr.sin_addr.s_addr, sizeof(out_addr.sin_addr.s_addr));
	}
	else if (areq.atype == 3)
	{
		// domain
		char len;
		recv_n(in, (char *)&len, 1);
		char domain[256];
		recv_n(in, domain, len);
		domain[len] = '\0';
		hostent *host = gethostbyname(domain);
		if (!host || host->h_addrtype != AF_INET || host->h_length <= 0)
		{
			cout << "protocol error" << endl;
			return 9;
		}
		memcpy(&out_addr.sin_addr.s_addr, host->h_addr_list[0], 
			sizeof(out_addr.sin_addr.s_addr));
	}
	else
	{
		// 每有这种情况
		assert(0);
	}
	
	recv_n(in, (char *)&out_addr.sin_port, sizeof(out_addr.sin_port));


	// 服务器对请求响应
	int out = socket(AF_INET, SOCK_STREAM, 0);
	if (out < 0)
	{
		perror("socket");
		return 10;
	}

	if (connect(out, (sockaddr *)&out_addr, sizeof(out_addr)) < 0)
	{
		perror("connect");
		return 11;
	}
	
	AddrRep arep;
	arep.ver = 5;
	arep.cmd = 0;
	arep.rsv = 0;
	arep.atype = 1;
	sockaddr_in local_addr;
	socklen_t length = sizeof(local_addr);
	getsockname(out, (sockaddr *)&local_addr, &length);
	memcpy(&arep.addr, &local_addr.sin_addr.s_addr, 
		sizeof(local_addr.sin_addr.s_addr));

	memcpy(&arep.port, &local_addr.sin_port, sizeof(short));
	send_n(in, (char *)&arep, sizeof(arep));


	Param up = {in, out, 0};
	Param down = {out, in, 0};

	pthread_create(&down.bro, NULL, transfer, &up);
	pthread_create(&up.bro, NULL, transfer, &down);

	pthread_join(down.bro, NULL);
	pthread_join(up.bro, NULL);

	return 0;
}
