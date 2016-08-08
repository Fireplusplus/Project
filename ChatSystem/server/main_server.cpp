#include "udp_server.h"

int main(int argc, char *argv[])
{
	daemon(0, 0);

	if (3 != argc)
	{
		usage("");
		exit(1);
	}

	std::string _ip = argv[1];
	short _port = atoi(argv[2]);
	udp_server _ser(_ip, _port);
	_ser.init();
	
	pthread_t th_recv, th_send;
	pthread_create(&th_recv, NULL, recv_product, (void*)&_ser);
	pthread_create(&th_send, NULL, send_consum, (void*)&_ser);
	
	pthread_join(th_recv, NULL);
	pthread_join(th_send, NULL);

	//while (1)
	//{
	//	ssize_t _ret = 0;
	//	std::string client_data;
	//	client_data.resize(_SIZE_);
	//	_ret = _ser.udp_recv(client_data);
	//	if (_ret > 0)
	//	{
	//		std::cout<< "client: ";
	//		std::cout<< client_data << std::endl;
	//	}
	//}

	return 0;
}
