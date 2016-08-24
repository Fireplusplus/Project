#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>

#include "comm.h"
#include "transfer.h"

const int _SIZE_ = 1024 * 1024;

void * transfer(void *p)
{
	Param *param = (Param *)p;
	int in = param->in;
	int out = param->out;
	int brother = param->bro;
	char buf[_SIZE_];
	
	while (true)
	{
		int ret = recv(in, buf, _SIZE_, 0);
		if (ret <= 0)
		{
			break;
		}
		
		ret = send_n(out, buf, ret);
		if (ret < 0)
		{
			break;
		}
	}

	close(in);
	close(out);
	pthread_cancel(brother);
	
	return NULL;
}
