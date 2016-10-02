#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include "mysql.h"

using namespace std;

class sql_api{
	public:
		sql_api();

		void my_connect();
		void my_insert(const string &data);
		void my_select();
		void my_close();

		~sql_api();
	private:
		MYSQL *conn;
		MYSQL_RES *res;
};









