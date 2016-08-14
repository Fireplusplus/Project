#include "ping.h"

char SendBuffer[SEND_BUFFER_SIZE];
char RecvBuffer[RECV_BUFFER_SIZE];
int nRecv = 0;	//实际接收到的报文数
struct timeval FirstSendTime;	//用以计算总的时间
struct timeval LastRecvTime;
double min = 0.0;
double avg = 0.0;
double max = 0.0;
double mdev = 0.0;

u_int16_t Compute_cksum(struct icmp *pIcmp)
{
	u_int16_t *data = (u_int16_t *)pIcmp;
	int len = ICMP_LEN;
	u_int32_t sum = 0;
	
	while (len > 1)
	{
		sum += *data++;
		len -= 2;
	}
	if (1 == len)
	{
		u_int16_t tmp = *data;
		tmp &= 0xff00;
		sum += tmp;
	}

	//ICMP校验和带进位
	while (sum >> 16)
		sum = (sum >> 16) + (sum & 0x0000ffff);
	sum = ~sum;
	
	return sum;
}

void SetICMP(u_int16_t seq)
{
	struct icmp *pIcmp;
	struct timeval *pTime;

	pIcmp = (struct icmp*)SendBuffer;
	
	/* 类型和代码分别为ICMP_ECHO,0代表请求回送 */
	pIcmp->icmp_type = ICMP_ECHO;
	pIcmp->icmp_code = 0;
	pIcmp->icmp_cksum = 0;		//校验和
	pIcmp->icmp_seq = seq;		//序号
	pIcmp->icmp_id = getpid();	//取进程号作为标志
	pTime = (struct timeval *)pIcmp->icmp_data;
	gettimeofday(pTime, NULL);	//数据段存放发送时间
	pIcmp->icmp_cksum = Compute_cksum(pIcmp);
	
	if (1 == seq)
		FirstSendTime = *pTime;
}

//可以对超时时间做个限制，每发出一个报文，设定闹钟，时间为2*rtt，
//再注册SIGALRM信号处理函数打印Destination Host Unreachable
//鉴于超时后还有可能收到ICMP报文，所以此处不处理
void SendPacket(int sock_icmp, struct sockaddr_in *dest_addr, int nSend)
{
	SetICMP(nSend);
	if (sendto(sock_icmp, SendBuffer, ICMP_LEN, 0,
		(struct sockaddr *)dest_addr, sizeof(struct sockaddr_in)) < 0)
	{
		perror("sendto");
		return;
	}
}

double GetRtt(struct timeval *RecvTime, struct timeval *SendTime)
{
	struct timeval sub = *RecvTime;

	if ((sub.tv_usec -= SendTime->tv_usec) < 0)
	{
		--(sub.tv_sec);
		sub.tv_usec += 1000000;
	}
	sub.tv_sec -= SendTime->tv_sec;
	
	return sub.tv_sec * 1000.0 + sub.tv_usec / 1000.0; //转换单位为毫秒
}

int unpack(struct timeval *RecvTime)
{
	struct ip *Ip = (struct ip *)RecvBuffer;
	struct icmp *Icmp;
	int ipHeadLen;
	double rtt;

	ipHeadLen = Ip->ip_hl << 2;	//ip_hl字段单位为4字节
	Icmp = (struct icmp *)(RecvBuffer + ipHeadLen);

	//判断接收到的报文是否是自己所发报文的响应
	if ((Icmp->icmp_type == ICMP_ECHOREPLY) && Icmp->icmp_id == getpid())
	{
		struct timeval *SendTime = (struct timeval *)Icmp->icmp_data;
		rtt = GetRtt(RecvTime, SendTime);
	
		printf("%u bytes from %s: icmp_seq=%u ttl=%u time=%.1f ms\n",
			ntohs(Ip->ip_len) - ipHeadLen,
			inet_ntoa(Ip->ip_src),
			Icmp->icmp_seq,
			Ip->ip_ttl,
			rtt);
		
		if (rtt < min || 0 == min)
			min = rtt;
		if (rtt > max)
			max = rtt;
		avg += rtt;
		mdev += rtt * rtt;
		
		return 0;
	}
		
	return -1;
}


void Statistics(int signo)
{
	double tmp;
	avg /= nRecv;
	tmp = mdev / nRecv - avg * avg;
	mdev = sqrt(tmp);
	
	if (NULL != pHost)
		printf("--- %s  ping statistics ---\n", pHost->h_name);
	else
		printf("--- %s  ping statistics ---\n", IP);
		
	printf("%d packets transmitted, %d received, %d%% packet loss, time %dms\n"
		, nSend
		, nRecv
		, (nSend - nRecv) / nSend * 100
		, (int)GetRtt(&LastRecvTime, &FirstSendTime));
	printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n",
		min, avg, max, mdev);
	
	close(sock_icmp);
	exit(0);
}

int RecvePacket(int sock_icmp, struct sockaddr_in *dest_addr)
{
	int RecvBytes = 0;
	int addrlen = sizeof(struct sockaddr_in);
	struct timeval RecvTime;

	if ((RecvBytes = recvfrom(sock_icmp, RecvBuffer, RECV_BUFFER_SIZE,
			0, (struct sockaddr *)dest_addr, &addrlen)) < 0)
	{
		perror("recvfrom");
		return 0;
	}
	//printf("nRecv=%d\n", RecvBytes);
	gettimeofday(&RecvTime, NULL);
	LastRecvTime = RecvTime;

	if (unpack(&RecvTime) == -1)
	{
		return -1; 
	}
	nRecv++;
}

