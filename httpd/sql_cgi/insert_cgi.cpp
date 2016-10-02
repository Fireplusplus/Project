#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <string>
#include "sql_api.h"
using namespace std;

void my_insert(char *arg)
{
	// name="tom"&school="qinghua"&hobby="coding"
	char *vec[3] = {NULL, NULL};

	int i = 2;
	char *end = arg+strlen(arg)-1;
	while(end > arg){
		if( *(end-1)== '=' ){
			vec[i--] = end;
		}
		if(*end == '&'){
			*end = '\0';
		}
		end--;
	}

	string data = "'";
	data += vec[0];
	data += "', ";
	data += "'";
	data += vec[1];
	data += "',";
	data += "'";
	data += vec[2];
	data += "'";

	sql_api api;
	api.my_connect();
	api.my_insert(data);
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
	

	my_insert(buf);


	return 0;
}










