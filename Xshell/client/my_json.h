#pragma once 

#include "json\json.h"
#include <string>

class my_json
{
public:
	static void serialize(Json::Value &val, std::string &out);

	static void un_serialize(Json::Value &val, std::string &out);
};
