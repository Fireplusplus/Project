#include "comm.h"

void print_log(const char *const err_msg, const char *const fun_name, int line)
{
	std::cout<< err_msg << " ["<< fun_name<< "] "<< line<< std::endl;
	
}

void usage(const char *proc)
{
	std::cout<< "Usage : " << proc<< " [ip] [port]"<< std::endl;
}

