#pragma once

#include <iostream>
#include <string>
#include <ncurses.h>
#include "comm.h"
#include <string.h>

class chat_window
{
public:
	chat_window();
	
	WINDOW * create_newwin(int height, int weight, int start_y, int start_x);

	void flush_window(WINDOW *_win);
	
	void put_str(WINDOW *_win, int _y, int _x, std::string &str);
	void get_str(WINDOW *_win, std::string &out);
	
	void clear_win_line(WINDOW *_win, int begin_y, int nums);
	~chat_window();
	
	void create_header();
	void create_output();
	void create_flist();
	void create_input();

public:
	WINDOW *header;
	WINDOW *output;
	WINDOW *flist;
	WINDOW *input;
};

