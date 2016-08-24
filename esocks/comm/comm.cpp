#include "comm.h"

#include <sys/types.h>
#include <sys/socket.h>

int recv_n(int sock, char *buf, int len)
{
	char *cur = buf;
	int left = len;
	while (left > 0)	
	{
		int ret = recv(sock, cur, left, 0);
		if (ret <= 0)
			return -1;
		cur += ret;
		left -= ret;
	}

	// 接收到进行解密
	encryption(buf, len);

	return 0;
}

int send_n(int sock, char *buf, int len)
{
	// 发送前加密
	encryption(buf, len);

	char *cur = buf;
	int left = len;
	while (left > 0)
	{
		int ret = send(sock, cur, left, 0);
		if (ret < 0)
			return -1;
		cur += ret;
		left -= ret;
	}
	
	return 0;
}

// 简单异或运算，使数据内容初步被识别
void encryption(char *buf, int len)
{
	for (int i = 0; i < len; i++)
	{
		// 0101
		buf[i] ^= 5;
	}
}






