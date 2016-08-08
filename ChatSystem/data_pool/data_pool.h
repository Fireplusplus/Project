#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <semaphore.h>

#define _size 128

class data_pool
{
public:
	data_pool(int sz = _size);
	~data_pool();
	void data_get(std::string &msg_out);
	void data_put(const std::string &msg);

private:
	std::vector<std::string> pool;
	int cap;

	int index_pro;
	int index_con;
	
	sem_t blank_sem;
	sem_t data_sem;
};
