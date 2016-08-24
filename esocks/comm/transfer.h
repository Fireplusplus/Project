#pragma once

// 线程函数参数
struct Param
{
	int in;
	int out;
	pthread_t bro;
};


void * transfer(void *p);
