#include "udp_server.h"


udp_server::udp_server(const std::string &_ip, short _port)
	: ip(_ip)
	, port(_port)
	, sock(-1)
{}

udp_server::~udp_server()
{
	if (1 != sock)
		close(sock);
}

void udp_server::init()
{
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
	{
		print_log(strerror(errno), __FUNCTION__, __LINE__);
		exit(1);
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip.c_str());

	if (bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0)
	{
		print_log(strerror(errno), __FUNCTION__, __LINE__);
		exit(1);
	}
}

ssize_t udp_server::udp_recv(std::string &out)
{
	struct sockaddr_in client;
	socklen_t len = sizeof(client);
	char buf[_SIZE_];
	memset(buf, '\0', sizeof(buf));
	ssize_t _ret = recvfrom(sock, buf, sizeof(buf)-1, 0, (struct sockaddr*)&client, &len);
	if (_ret > 0)
	{
		out = buf;
		add_user(client);
		old_user_del(client, out);
		
		//std::cout << out << std::endl;

		pool.data_put(out);
	}
	else
	{
		print_log(strerror(errno), __FUNCTION__, __LINE__);
	}
	return _ret;
}

ssize_t udp_server::udp_send(std::string &in, struct sockaddr_in &cli, socklen_t len)
{
	ssize_t _ret = sendto(sock, in.c_str(), in.size(), 0, (struct sockaddr*)&cli, len);
	if (_ret < 0)
	{
		print_log(strerror(errno), __FUNCTION__, __LINE__);	
	}
	return _ret;
}


void udp_server::add_user(struct sockaddr_in &client)
{
	std::string key_ip = inet_ntoa(client.sin_addr);
	std::map<std::string, struct sockaddr_in>::iterator _ite;

	_ite = online_user.find(key_ip);
	if (online_user.end() == _ite)
	{
		online_user.insert(std::pair<std::string, struct sockaddr_in>(key_ip, client));	
	}
}

void udp_server::old_user_del(struct sockaddr_in &client, std::string &in)
{
	udp_data data;
	data.to_value(in);
	std::string _cmd;
	data.get_cmd(_cmd);
	if ("Q" == _cmd)
	{
		std::string key_ip = inet_ntoa(client.sin_addr);
      		online_user.erase(key_ip);
	}
}

void udp_server::broadcast()
{
	std::map<std::string, struct sockaddr_in>::iterator _ite;
	
	std::string _msg;
	pool.data_get(_msg);

	for (_ite = online_user.begin(); _ite != online_user.end(); ++_ite)
	{
		udp_send(_msg, _ite->second, sizeof(_ite->second));
	}
}


void * recv_product(void *arg)
{
	udp_server *_serp = (udp_server*)arg;
	bool done = false;
	std::string _msg;
	while (!done)
	{
		_serp->udp_recv(_msg);
	}
	return NULL;
}

void * send_consum(void *arg)
{
	udp_server *_serc = (udp_server*)arg;
	bool done = false;
	while (!done)
	{
		_serc->broadcast();
	}
	return NULL;
}	
