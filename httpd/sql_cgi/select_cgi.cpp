#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <string>
#include "sql_api.h"

using namespace std;

void my_select(char *arg)
{
	sql_api api;
	api.my_connect();
	api.my_select();
	return;
}

int main()
{
	string method;
	string query_string;
	string content_length;
	int len = -1;
	char buf[1024];

	if(getenv("METHOD") != NULL){
		method = getenv("METHOD");
		cout<<method<<endl;
	}
	if( strcasecmp(method.c_str(), "get") == 0 ){
		query_string = getenv("QUERY_STRING");
		strcpy(buf, query_string.c_str());
	}else if( strcasecmp(method.c_str(), "post") == 0 ){
		content_length = getenv("CONTENT_LENGTH");
		len = atoi(content_length.c_str());
		int i = 0;
		for(; i < len; i++ ){
			read(0, &buf[i], 1);
		}
	}else{
	}
	//arg -> buf
	my_select(buf);
	return 0;
}










