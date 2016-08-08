#include "chat_window.h"

chat_window::chat_window()
{
	initscr();
	curs_set(0);
}

WINDOW * chat_window::create_newwin(int height, int weight, int start_y, int start_x)
{
	WINDOW *local_win = newwin(height, weight, start_y, start_x);	
	box(local_win, 0, 0);
	
	return local_win;
}

void chat_window::flush_window(WINDOW *_win)
{
	wrefresh(_win);
}

void chat_window::put_str(WINDOW *_win, int _y, int _x, std::string &str)
{
	mvwaddstr(_win, _y, _x, str.c_str());
}

void chat_window::get_str(WINDOW *_win, std::string &out)
{
	char msg[_SIZE_];
	memset(msg, '\0', sizeof(msg));
	wgetnstr(_win, msg, _SIZE_);
	out = msg;
}

void chat_window::clear_win_line(WINDOW *_win, int begin_y, int nums)
{
	while (nums-- > 0)
	{
		wmove(_win, begin_y++, 0);
		wclrtoeol(_win);
	}
}

void chat_window::create_header()
{
	int start_y = 0;
	int start_x = 0;
	int height = LINES / 5;
	int weight = COLS;
	header = create_newwin(height, weight, start_y, start_x);
}

void chat_window::create_output()
{
	int start_y = LINES / 5;
	int start_x = 0;
	int height = (LINES * 3) / 5;
	int weight = (COLS * 3) / 4;
	output = create_newwin(height, weight, start_y, start_x);
}

void chat_window::create_flist()
{
	int start_y = LINES / 5;
	int start_x = (COLS * 3) / 4;
	int height = (LINES * 3) / 5;
	int weight = COLS / 4;
	flist = create_newwin(height, weight, start_y, start_x);
}

void chat_window::create_input()
{
	int start_y = (LINES * 4) / 5;
	int start_x = 0;
	int height = LINES / 5;
	int weight = COLS;
	input = create_newwin(height, weight, start_y, start_x);
}

chat_window::~chat_window()
{
	delwin(header);
	delwin(output);
	delwin(flist);
	delwin(input);
	endwin();
}
