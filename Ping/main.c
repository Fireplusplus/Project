#include "ping.h"


struct hostent * pHost = NULL;		//保存主机信息
int sock_icmp;				//icmp套接字
int nSend = 1;
char *IP = NULL;

void Call(int argc, char *argv[])
{

	struct protoent *protocol;
	struct sockaddr_in dest_addr; 	//IPv4专用socket地址,保存目的地址

	in_addr_t inaddr;		//ip地址（网络字节序）

	if (argc < 2)
	{
		printf("Usage: %s [hostname/IP address]\n", argv[0]);
		exit(EXIT_FAILURE);	
	}

	if ((protocol = getprotobyname("icmp")) == NULL)
	{
		perror("getprotobyname");
		exit(EXIT_FAILURE);
	}

	/* 创建ICMP套接字 */
	//AF_INET:IPv4, SOCK_RAW:IP协议数据报接口, IPPROTO_ICMP:ICMP协议
	if ((sock_icmp = socket(PF_INET, SOCK_RAW, protocol->p_proto/*IPPROTO_ICMP*/)) < 0)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	dest_addr.sin_family = AF_INET;

	/* 将点分十进制ip地址转换为网络字节序 */
	if ((inaddr = inet_addr(argv[1])) == INADDR_NONE)
	{
		/* 转换失败，表明是主机名,需通过主机名获取ip */
		if ((pHost = gethostbyname(argv[1])) == NULL)
		{
			herror("gethostbyname()");
			exit(EXIT_FAILURE);
		}
		memmove(&dest_addr.sin_addr, pHost->h_addr_list[0], pHost->h_length);
	}
	else
	{
		memmove(&dest_addr.sin_addr, &inaddr, sizeof(struct in_addr));
	}

	if (NULL != pHost)
		printf("PING %s", pHost->h_name);
	else
		printf("PING %s", argv[1]);
	printf("(%s) %d bytes of data.\n", inet_ntoa(dest_addr.sin_addr), ICMP_LEN);

	IP = argv[1];
	signal(SIGINT, Statistics);
	while (nSend < SEND_NUM)
	{
		int unpack_ret;
		
		SendPacket(sock_icmp, &dest_addr, nSend);
		
		unpack_ret = RecvePacket(sock_icmp, &dest_addr);
		if (-1 == unpack_ret)	//（ping回环时）收到了自己发出的报文,重新等待接收
			RecvePacket(sock_icmp, &dest_addr);
			

		sleep(1);
		nSend++;
	}
	
	Statistics(0);	//输出信息，关闭套接字
}

int main(int argc, char *argv[])
{
	Call(argc, argv);

	return 0;
}
