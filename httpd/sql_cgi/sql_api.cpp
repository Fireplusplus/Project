#include "sql_api.h"


sql_api::sql_api()
{
	conn = mysql_init(NULL);
	res = NULL;
}

void sql_api::my_connect()
{
	if( !mysql_real_connect(conn, "127.0.0.1","root","admin", "httpd", 3306, NULL, 0)){
		cout<<"connect error!\n"<<endl;
	}else{
		cout<<"connect success!\n"<<endl;
	}
}

void sql_api::my_insert(const string &data)
{
	string sql = "INSERT INTO student (name, school, hobby) values (";
	sql += data;
	sql += ")";
	cout<<sql<<endl;
	mysql_query(conn, sql.c_str());
}

void sql_api::my_select()
{
	string sql = "SELECT * FROM student";
	if(mysql_query(conn, sql.c_str()) == 0){
		 res = mysql_store_result(conn);
		 if(res){
			 int rows = mysql_num_rows(res);
			 int cols = mysql_num_fields(res);

			 cout<<"rows: "<<rows<<endl;
			 cout<<"cols: "<<cols<<endl;
			 MYSQL_FIELD *fd = NULL;
			 for(; fd = mysql_fetch_field(res); ){
				 cout<<fd->name<<"\t";
			 }
			 cout<<endl;

			 int i = 0;
			 for( ; i < rows; i++ ){
				 MYSQL_ROW line = mysql_fetch_row(res);
				 int j = 0;
				 for(; j < cols; j++ ){
					 cout<<line[j]<<"\t";
				 }
				 cout<<endl;
			 }
		 }
	}
}

void sql_api::my_close()
{
	mysql_close(conn);
	if( res != NULL ){
		free(res);
		res = NULL;
	}
}

sql_api::~sql_api()
{
	my_close();
}




