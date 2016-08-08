#include "my_json.h"


void my_json::serialize(Json::Value &val, std::string &out)
{
//#ifdef _DEBUG_
	Json::FastWriter write;
//#else	
//	Json::StyledWriter write;
//#endif
	out = write.write(val);
}
	
void my_json::un_serialize(Json::Value &val, std::string &out)
{
	Json::Reader read;

	read.parse(out, val, false);
}
