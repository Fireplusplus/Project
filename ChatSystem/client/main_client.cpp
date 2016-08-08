#include "udp_client.h"
#include <stdio.h>
#include <unistd.h>
#include "udp_data.h"
#include "chat_window.h"
	
struct sockaddr_in *ser_p;
socklen_t len;

chat_window *win_p;
std::string _nick_name;
std::string _school;
std::string _cmd = "None";

void * draw_header(void *arg)
{
	udp_client *cli_p = (udp_client *)arg;
	win_p->create_header();
	
	sem_wait(&(cli_p->lock));
	win_p->flush_window(win_p->header);
	sem_post(&(cli_p->lock));

	int max_y, max_x;
	getmaxyx(win_p->header, max_y, max_x);
	std::string head_line = "Chat System";

	int index = 1;

      while (1)
      {
		win_p->put_str(win_p->header, max_y / 2, index++, head_line);
		if (index >= (max_x * 3) / 4)
		{
			index = 1;
		}
	
		sem_wait(&(cli_p->lock));
		win_p->flush_window(win_p->header);
		sem_post(&(cli_p->lock));
		
		usleep(500000);
		win_p->clear_win_line(win_p->header, max_y / 2, 1);
		box(win_p->header, 0, 0);
	}

	return NULL;
}

void * draw_output(void *arg)
{
	udp_client *cli_p = (udp_client *)arg;

	win_p->create_output();
	win_p->create_flist();


	sem_wait(&(cli_p->lock));
	win_p->flush_window(win_p->output);
	sem_post(&(cli_p->lock));
	sem_wait(&(cli_p->lock));
	win_p->flush_window(win_p->flist);
	sem_post(&(cli_p->lock));


	std::string _recv_str;
	std::string flist_str;	
	udp_data data;

	std::string _nn;
	std::string _s;
	std::string _c;
	std::string _m;

	int max_oy, max_ox;
	getmaxyx(win_p->output, max_oy, max_ox);
	int max_fy, max_fx;
	getmaxyx(win_p->flist, max_fy, max_fx);

	int index = 1;
	int page_num = 0;
	while (1)
	{
		cli_p->udp_recv(_recv_str);
		
		data.to_value(_recv_str);
		data.get_nick_name(_nn);
		data.get_school(_s);
		data.get_msg(_m);
		data.get_cmd(_c);

		std::string _win_str;
		_win_str += _nn;
		_win_str += "-";
		_win_str += _s;
	
		flist_str = _win_str;
		
		_win_str += "# ";
		_win_str += _m;

		
		sem_wait(&(cli_p->lock));
		cli_p->add_flist(flist_str);
		sem_post(&(cli_p->lock));
		sem_wait(&(cli_p->lock));
		if  (_c == "Q")
		{
			std::vector<std::string>::iterator pos;
			for (pos = cli_p->flist.begin(); pos != cli_p->flist.end();)
			{
				if (*pos == flist_str)
				{
					pos = cli_p->flist.erase(pos);
					break;
				}
				else
				{
					++pos;
				}
			}
		}
		sem_post(&(cli_p->lock));
	
		win_p->put_str(win_p->output, index++, 1, _win_str);
		if (index >= max_oy)
		{
			index = 1;
			win_p->clear_win_line(win_p->output, 1, max_oy);
			win_p->put_str(win_p->output, index++, 1, _win_str);
		}
		win_p->clear_win_line(win_p->flist, 1, max_fy);

		int nums = cli_p->flist.size();
		int page = max_fy - 3;
		int pages = nums / page;
		int last_page = nums % page;
		
		if (0 != last_page)
			++pages;
		
		page_num %= pages;
		for (; page_num < pages; ++page_num)
		{
			int i = 0;
	        	for (; i < page; ++i)
	        	{
				int k = page_num * page + i;
	        		win_p->put_str(win_p->flist, i + 1, 3, cli_p->flist[k]);
	        		if (i == last_page - 1)
					break;
			}
			if (page_num == pages - 1)
				break;
		}
		
		std::string page_line;
		std::strstream ss1;
		std::strstream ss2;
		ss1 << (page_num + 1);
		ss1 >> page_line;
		page_line += "/";
		std::string p_str;
		ss2 << pages;
		ss2 >> p_str;
		page_line += p_str;
	        win_p->put_str(win_p->flist, max_fy - 2, max_fx / 2 - 1, page_line);
			
		
		box(win_p->flist, 0, 0);
		box(win_p->output, 0, 0);
		sem_wait(&(cli_p->lock));
		win_p->flush_window(win_p->flist);
		sem_post(&(cli_p->lock));
		sem_wait(&(cli_p->lock));
		win_p->flush_window(win_p->output);
		sem_post(&(cli_p->lock));
	}
	
	return NULL;
}

void * draw_flist(void *arg)
{
//	udp_client *cli_p = (udp_client *)arg;
//	win_p->create_flist();
//	
//	sem_wait(&(cli_p->lock));
//	win_p->flush_window(win_p->flist);
//	sem_post(&(cli_p->lock));
	

	while (1)
	{
	//	sem_wait(&(cli_p->lock));
	//	win_p->flush_window(win_p->flist);
	//	sem_post(&(cli_p->lock));
		sleep(1);	
	}
	
	return NULL;
}

void * draw_input(void *arg)
{
	udp_client *cli_p = (udp_client *)arg;

	std::string cmd_line = "Please Enter# ";
	win_p->create_input();
	std::string _win_str;
	std::string send_str;

	udp_data data;
	
	while (1)
	{
		win_p->put_str(win_p->input, 1, 1, cmd_line);
		box(win_p->input, 0, 0);
		
		sem_wait(&(cli_p->lock));
		win_p->flush_window(win_p->input);
		sem_post(&(cli_p->lock));	
		
		win_p->get_str(win_p->input, _win_str);
		win_p->clear_win_line(win_p->input, 1, 1);
		
		if ("quit" == _win_str)
			_cmd = "Q";

		data.set_nick_name(_nick_name);
		data.set_school(_school);
		data.set_cmd(_cmd);
		data.set_msg(_win_str);

		data.to_string(send_str);

		cli_p->udp_send(send_str, *ser_p, len);
		usleep(100000);

		if ("Q" == _cmd)
			exit(0);
	}
	
	return NULL;
}

int main(int argc, char *argv[])
{
	if (3 != argc)
	{
		usage("");
		exit(1);	
	}
	
	std::cout<< "Please enter your nick name # ";
	fflush(stdout);
	std::cin>> _nick_name;
	std::cout<< "Please enter your school name # ";
	fflush(stdout);
	std::cin>> _school;
	getchar();

	udp_client _cli;
	_cli.init();

	chat_window win;
	win_p = &win;

	struct sockaddr_in _ser;
	_ser.sin_family = AF_INET;
	_ser.sin_port = htons(atoi(argv[2]));
	_ser.sin_addr.s_addr = inet_addr(argv[1]);
	len = sizeof(_ser);
	ser_p = &_ser;

	pthread_t header, output, flist, input;
	pthread_create(&header, NULL, draw_header, (void *)&_cli);
	pthread_create(&output, NULL, draw_output, (void *)&_cli);
	//pthread_create(&flist, NULL, draw_flist, (void *)&_cli);
	pthread_create(&input, NULL, draw_input, (void *)&_cli);

	pthread_join(header, NULL);
	pthread_join(output, NULL);
	//pthread_join(flist, NULL);
	pthread_join(input, NULL);

//	while (1)
//	{
//		std::cout<< "Please Enter# ";
//		fflush(stdout);
//		char buf[_SIZE_];
//		memset(buf, '\0', sizeof(buf));
//		ssize_t _ret = read(0, buf, sizeof(buf) - 1);	
//		buf[_ret - 1] = '\0';
//
//		std::string data = buf;
//		if (_ret > 0)
//		{
//			data = buf;
//			
//			u_data.set_nick_name(nick_name);
//			u_data.set_school(school);
//			u_data.set_msg(data);
//			u_data.set_cmd(cmd);
//			u_data.to_string(send_msg);
//
//			ssize_t n = _cli.udp_send(send_msg, _ser, len);
//		}
//
//		data = "";
//		_cli.udp_recv(data);
//		std::cout<< data<< std::endl;
//	}

	return 0;
}
