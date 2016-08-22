#include "data.h"

data::data()
{}


void data::get_msg(std::string &out)
{
	out = msg;
}

void data::get_cmd_line(std::string &out)
{
	out = cmd_line;
}

void data::set_msg(std::string &out)
{
	msg = out;
}

void data::set_cmd_line(std::string &out)
{
	cmd_line = out;
}

void data::to_string(std::string &_sstr_out)
{
	Json::Value val;

	val["msg"] = msg;
	val["cmd_line"] = cmd_line;

	my_json::serialize(val, _sstr_out);
}

void data::to_value(std::string &_sstr_in)
{
	Json::Value val;
	my_json::un_serialize(val, _sstr_in);

	msg = val["msg"].asString();
	cmd_line = val["cmd_line"].asString();
}

data::~data()
{}
