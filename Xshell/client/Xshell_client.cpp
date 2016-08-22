#include "Xshell_client.h"


SOCKET init(const char *_ip, short _port)
{
	SOCKADDR_IN remote;

	WORD wVersionRequested;
	WSADATA wsaData;    // 用于接收Wjndows Socket的结构信息的  
	wVersionRequested = MAKEWORD(1, 1);  
	if (WSAStartup(wVersionRequested, &wsaData) != 0) {
		exit(1);
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sock)
	{
		printf("socket error\n");
		exit(2);
	}

	remote.sin_family = AF_INET;
	remote.sin_port = htons(_port);
	remote.sin_addr.S_un.S_addr = inet_addr(_ip);
	if (connect(sock, (SOCKADDR*)&remote, sizeof(remote)) == SOCKET_ERROR)
	{
		int ret = WSAGetLastError();
		printf("connect error: errno = %d\n", ret);
		exit(3);
	}
	
	return sock;
}

void recving(int sock, std::string &out)
{
	char buf[_SIZE_];
	memset(buf, '\0', sizeof(buf));
	int _s = recv(sock, buf, sizeof(buf) - 1, 0);
	if (_s <= 0)
	{
		std::cout << "recving error..." << std::endl;
		Sleep(0.5);
		exit(0);
	}
	buf[_s] = '\0';
	out = buf;
}

void sending(int sock, std::string &in)
{
	const char *buf = in.c_str();

	int _s = send(sock, buf, strlen(buf), 0);
	if (_s <= 0)
	{
		std::cout << "sending error..." << std::endl;
	}
}

