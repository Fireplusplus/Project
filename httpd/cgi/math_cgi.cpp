#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

using namespace std;

void math(char *arg)
{
	char* vec[2] = {0};
	int i = 1;
	char* end = arg+strlen(arg)-1;
	while (end > arg)
	{
		if (*(end-1) == '=')
			vec[i--] = end;
		if (*end == '&')
			*end = '\0';
		end--;
	}

	int data1 = atoi(vec[0]);
	int data2 = atoi(vec[1]);

	cout<<data1<<" + "<<data2<<" = "<<data1+data2<<endl;
	cout<<data1<<" - "<<data2<<" = "<<data1-data2<<endl;
	cout<<data1<<" * "<<data2<<" = "<<data1*data2<<endl;
	cout<<data1<<" / "<<data2<<" = "<<data1/data2<<endl;
	cout<<data1<<" % "<<data2<<" = "<<data1%data2<<endl;
}

int main()
{
	string method;
	string query_string;
	string content_length;
	int len = -1;
	char buf[1024];

	if (getenv("METHOD") != NULL)
	{
		method = getenv("METHOD");
		cout << method << endl;
	}
	else
		return 1;

	if (strcasecmp(method.c_str(), "get") == 0)
	{
		query_string = getenv("QUERY_STRING");
		strcpy(buf, query_string.c_str());
	}
	else if (strcasecmp(method.c_str(), "post") == 0)
	{
		content_length = getenv("CONTENT_LENGTH");
		len = atoi(content_length.c_str());
		int i = 0;
		for (; i < len; i++)
			read(0, buf+i, 1);
	}
	else
	{}

	math(buf);
	return 0;
}
