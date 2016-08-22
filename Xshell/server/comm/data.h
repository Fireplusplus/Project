#pragma once

#include <string>
#include "my_json.h"

class data
{
public:
	data();

	void get_cmd_line(std::string &out);
	void get_msg(std::string &out);

	void set_cmd_line(std::string &out);
	void set_msg(std::string &out);

	void to_string(std::string &_str_out);
	void to_value(std::string &_sstr_in);

	~data();

private:
	std::string cmd_line;
	std::string msg;
};
