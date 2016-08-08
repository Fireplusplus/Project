#include "udp_data.h"



udp_data::udp_data()
{}

void udp_data::get_nick_name(std::string &out)
{
	out = nick_name;
}

void udp_data::get_school(std::string &out)
{
	out = school;
}

void udp_data::get_msg(std::string &out)
{
	out = msg;
}

void udp_data::get_cmd(std::string &out)
{
	out = cmd;
}

void udp_data::set_nick_name(std::string &out)
{
	nick_name = out;
}

void udp_data::set_school(std::string &out)
{
	school = out;
}

void udp_data::set_msg(std::string &out)
{
	msg = out;
}

void udp_data::set_cmd(std::string &out)
{
	cmd = out;
}

void udp_data::to_string(std::string &_sstr_out)
{
	Json::Value val;
	
	val["nick_name"] = nick_name;
	val["school"] = school;
	val["msg"] = msg;
	val["cmd"] = cmd;

	my_json::serialize(val, _sstr_out);
}

void udp_data::to_value(std::string &_sstr_in)
{
	Json::Value val;
	my_json::un_serialize(val, _sstr_in);
	
	nick_name = val["nick_name"].asString();
	school = val["school"].asString();
	msg = val["msg"].asString();
	cmd = val["cmd"].asString();
}

udp_data::~udp_data()
{}
