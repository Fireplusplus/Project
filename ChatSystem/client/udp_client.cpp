#include "udp_client.h"


udp_client::udp_client(const std::string &_remote_ip, short _remote_port)
	: remote_ip(_remote_ip)
	, remote_port(_remote_port)
	, sock(-1)
{
	sem_init(&lock, 0, 1);
}

udp_client::~udp_client()
{
	if (-1 != sock)
		close(sock);
	
	sem_destroy(&lock);	
}

void udp_client::init()
{
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
	{
		print_log(strerror(errno), __FUNCTION__, __LINE__);
		exit(1);
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(remote_port);
	local.sin_addr.s_addr = inet_addr(remote_ip.c_str());

}

ssize_t udp_client::udp_recv(std::string &out)
{
	struct sockaddr_in server;
	socklen_t len = sizeof(server);
	char buf[_SIZE_];
	memset(buf, '\0', sizeof(buf));
	ssize_t _ret = recvfrom(sock, buf, sizeof(buf)-1, 0, (struct sockaddr*)&server, &len);
	if (_ret > 0)
	{
		out = buf;
	}
	else
	{
		print_log(strerror(errno), __FUNCTION__, __LINE__);
	}
	return _ret;
}

ssize_t udp_client::udp_send(std::string &in, struct sockaddr_in &ser, socklen_t &len)
{
	ssize_t _ret = sendto(sock, in.c_str(), in.size(), 0, (struct sockaddr*)&ser, len);
	if (_ret < 0)
	{
		print_log(strerror(errno), __FUNCTION__, __LINE__);	
	}
	return _ret;
}

void udp_client::add_flist(std::string &user)
{
	for (int i = 0; i < flist.size(); ++i)
	{
		if (flist[i] == user)
			return;
	}
	flist.push_back(user);
}
