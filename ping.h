#ifndef __PING_H__
#define __PING_H__

#include <stdio.h>
#include <sys/time.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/ip_icmp.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <signal.h>
#include <math.h>

#define ICMP_DATA_LEN 56		//ICMP默认数据长度
#define ICMP_HEAD_LEN 8			//ICMP默认头部长度
#define ICMP_LEN  (ICMP_DATA_LEN + ICMP_HEAD_LEN)
#define SEND_BUFFER_SIZE 128		//发送缓冲区大小
#define RECV_BUFFER_SIZE 128		//接收缓冲区大小
#define SEND_NUM 100 			//发送报文数
#define MAX_WAIT_TIME 3

extern struct hostent *pHost;
extern int sock_icmp;
extern int nSend;
extern char *IP;

//发送ICMP报文
void SendPacket(int sock_icmp, struct sockaddr_in *dest_addr, int nSend);

//接收ICMP报文
int RecvePacket(int sock_icmp, struct sockaddr_in *dest_addr);

//计算校验和
u_int16_t Compute_cksum(struct icmp *pIcmp);

//设置ICMP报文
void SetICMP(u_int16_t seq);

//剥去报头
int unpack(struct timeval *RecvTime);

//计算往返时间
double GetRtt(struct timeval *RecvTime, struct timeval *SendTime);

//统计信息
void Statistics(int signo);


#endif	//__PING_H__
