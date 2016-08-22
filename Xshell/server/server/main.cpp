#include "xshell.h"
#include <pthread.h>

void * accept_request(void *arg)
{
	int sock = (int)(long long)arg;
	
	data d;
	std::string cmd_line;
	std::string msg;

	get_cmd_line(cmd_line);
	d.set_cmd_line(cmd_line);
	d.set_msg(msg);

	std::string str("");
	d.to_string(str);
	sending(sock, str);

	int done = 0;
	while (!done)
	{
		msg = "";
		if (recving(sock, msg) < 0)
		{
			std::cout << "remote reset connect" << std::endl;
			exit(1);
		}

		//std::cout << msg << std::endl;

		if (exec_command(msg) == -1)
		{
			break;
		}
		get_cmd_line(cmd_line);
		d.set_cmd_line(cmd_line);

		d.set_msg(result);
		d.to_string(str);

		//std::cout << "!!!result: " << result << std::endl;
		sending(sock, str);
	}

	close(sock);
}

static void usage(const char *name)
{
	printf("Usage: %s [ip] [port]\n", name);
}

int main(int argc, char *argv[])
{
	if (3 != argc)
	{
		usage(argv[0]);
		exit(-1);
	}
	
	int listen_sock = init(argv[1], atoi(argv[2]));

	//output = open("./output", O_RDWR | O_TRUNC);		
	//output = dup2(output, 1);
	//if (output < 0)
	//{
	//	perror("dup2");
	//	exit(-2);
	//}

	int done = 0;
	while (!done)
	{
		struct sockaddr_in peer;
		socklen_t len = sizeof(peer);
		int sock = accept(listen_sock, 
			(struct sockaddr *)&peer, &len);
		if (sock < 0)
		{
			perror("accept");
			exit(4);
		}	
		printf("user connect...%s:%d\n", inet_ntoa(peer.sin_addr), 
				ntohs(peer.sin_port));
		
		pthread_t th;
		pthread_create(&th, NULL, accept_request, (void *)sock);
		pthread_detach(th);
	}
	
	close(listen_sock);

	return 0;
}
