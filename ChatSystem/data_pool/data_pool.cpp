#include "data_pool.h"


data_pool::data_pool(int sz)
	: pool(sz)
	, cap(sz)
	, index_pro(0)
	, index_con(0)
{
	sem_init(&blank_sem, 0, sz);
	sem_init(&data_sem, 0, 0);
}
void data_pool::data_get(std::string &msg_out)
{
	sem_wait(&data_sem);
	
	msg_out = pool[index_con++];
	index_con %= cap;

	sem_post(&blank_sem);
}

void data_pool::data_put(const std::string &msg)
{
	sem_wait(&blank_sem);
	
	pool[index_pro++] = msg;
	index_pro %= cap;

	sem_post(&data_sem);
}
	
data_pool::~data_pool()
{
	sem_destroy(&blank_sem);	
	sem_destroy(&data_sem);	
}
