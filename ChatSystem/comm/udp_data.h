#pragma once

#include <string>
#include "my_json.h"

class udp_data
{
public:
	udp_data();
	
	void get_nick_name(std::string &out);
	void get_school(std::string &out);
	void get_msg(std::string &out);
	void get_cmd(std::string &out);
	
	void set_nick_name(std::string &out);
	void set_school(std::string &out);
	void set_msg(std::string &out);
	void set_cmd(std::string &out);
	
	void to_string(std::string &_str_out);
	void to_value(std::string &_sstr_in);
	
	~udp_data();

private:
	std::string nick_name;
	std::string school;
	std::string msg;
	std::string cmd;
};
