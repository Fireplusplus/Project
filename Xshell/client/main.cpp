#define _CRT_SECURE_NO_WARNINGS 1

#include "Xshell_client.h"


int main()
{
	//std::string ip("192.168.43.222"), port("6666");

	std::cout << "Please Enter [ip] & [port]" << std::endl;
	std::cin >> ip >> port;

	SOCKET sock = init((char *)ip.c_str(), atoi(port.c_str()));

	data d;

	int done = 0;
	char buf[_SIZE_];
	while (!done)
	{
		// recv
		std::string str;
		recving(sock, str);

		d.to_value(str);
		std::string cmd_line, msg;

		d.get_cmd_line(cmd_line);
		d.get_msg(msg);
		std::cout << msg << cmd_line;

		// send
		memset(buf, '\0', sizeof(buf));
		while (strlen(buf) == 0)
		{
			gets(buf); 
			std::cout << cmd_line;
			msg = buf;
		}
		//std::cout << "input cmd is : " << msg << std::endl;

		if (msg == "clear")
		{
			system("CLS");
			std::cout << cmd_line;
			gets(buf);
			msg = buf;
		}
		

		sending(sock, msg);
		
	}

	system("pause");
	return 0;
}
