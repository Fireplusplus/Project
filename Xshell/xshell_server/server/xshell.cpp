#include "xshell.h"
#include <list>
#include <ctype.h>
#include <pwd.h>
#include <unistd.h>

int listen_sock;

// 命令执行结果
std::string result;
const int _LINE_ = 100;

// 历史命令
std::list<std::string> history;
const int max_history_size = 500;

// alias
std::list<std::string> alias;
const int max_alias_size = 500;

// 内建命令
const char* builtins[] = {"cd", "help", "exit", "history", "!!", "alias", "unalias", NULL};
typedef int (*BUILTIN)(char* argv[]);
BUILTIN builtin[] = {&change_dir, &show_builtins, &do_exit, &show_history, &do_last, &do_alias, &do_unalias, NULL};
int builtin_size = 7; 		// !!!!!!!!!!!!!!!!!!!!update!!


int init(const char *ip, short port)
{
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);
	
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock < 0)
	{
		perror("socket");
		exit(1);
	}

	if (bind(listen_sock, (struct sockaddr *)&local, sizeof(local)) < 0)
	{
		perror("bind");
		exit(2);
	}
	
	if (listen(listen_sock, 5) < 0)
	{
		perror("listen");
		exit(3);
	}

	return listen_sock;
}

// 获取终端提示符
void get_cmd_line(std::string &out)
{
	out = "";
	
	// 获取用户名
	struct passwd *pwd = getpwuid(getuid());
	out += pwd->pw_name;
	out +="@";

	// 获取主机名
	char _name[128];
	memset(_name, '\0', sizeof(_name));
	gethostname(_name, sizeof(_name));
	out += _name;
	out += ":";

	// 获取当前工作目录
	char _dir[128];
	memset(_dir, '\0', sizeof(_dir));
	getcwd(_dir, sizeof(_dir));

	std::string tmp(_dir);
	if (tmp.size() > 1)
	{
		size_t pos = tmp.find_last_of("/");	
		std::string str(tmp, pos + 1);
		out += str;
	}
	else
		out += _dir;

	if (_name == "root")
		out += "# "; 
	else
		out += "$ ";
}

int recving(int fd, std::string &out)
{
	int _s;
	char _buf[_SIZE_];
	memset(_buf, '\0', sizeof(_buf));
	if ((_s = read(fd, _buf, sizeof(_buf) - 1)) <= 0)
	{
		perror("read");
		return -1;
	}
	_buf[_s] = '\0';
	out = _buf;
	return 0;
}

void sending(int _fd, const std::string &in)
{
	int _s;
	const char *_msg = in.c_str();
	if ((_s = write(_fd, _msg, strlen(_msg))) < 0)
	{
		perror("read");
		return;
	}
}

// 执行普通命令
void my_popen(std::string &cmd)
{
	std::cout << "my_popen: " << cmd << std::endl;

	char buf[_SIZE_];
	memset(buf, '\0', sizeof(buf));

	FILE *rs = popen(cmd.c_str(), "r");
	if (rs == NULL)
	{
		sprintf(buf, "popen: %s", strerror(errno));
		result = buf;
		return;
	}

	fread(buf, 1, sizeof(buf), rs);
	result = buf;
	if (result == "")
	{
		result += cmd;
		result += ": not found\n";
	}
	fclose(rs);
}

// 格式化命令串
void command_format(std::string &in, char* out[])
{
	char *str = (char *)in.c_str();
	char *end = str + strlen(str);
	int index = 0;

	out[index++] = str;
	while (str < end && !isspace(*str))
		str++;

	if (str == end)
		out[index++] = NULL;
	else
	{
		*str = '\0';
		out[index++] = str + 1;
		out[index] = NULL;
	}
	//printf("in:command_format: 1:%s 2:%s\n", out[0], out[1]);
}

// 区分执行内建命令与普通命令
int exec_command(std::string &cmd)
{
	if (cmd != "!!")
		add_histroy(cmd);
	else
		cmd = history.back();

	char* buf[10];
	std::string tmp(cmd);
	command_format(tmp, buf);

	// 别名转换 //q='ls -a'
	char *str = new char[128];	
	memset(str, '\0', 128);
	int len = strlen(buf[0]);	

	std::list<std::string>::iterator pos = alias.begin();
	int i = 0;
	for (; i < alias.size(); i++, ++pos)
	{
		if (strncmp(buf[0], pos->c_str(), len) == 0 && (*pos)[len] == '=')
		{
			size_t p = pos->find_first_of("=");
			strcpy(str, pos->c_str() + p + 1 + 1);
			str[strlen(str) - 1] = '\0';
			
			cmd = "";
			cmd += str;
			cmd += " ";
			if (buf[1] != NULL)
				cmd += buf[1];
			break;
		}
	}

	// 执行内建命令
	for (int i = 0; i < builtin_size; i++)
	{
		if (strcmp(buf[0], builtins[i]) == 0)
		{	
			int ret = (*builtin[i])(buf);
			delete[] str;
			return ret;
		}
	}
	
	// not builtin
	my_popen(cmd);
	
	delete[] str;
	return 0;	
}

// 内建命令

int change_dir(char* argv[])
{
	if (NULL == argv[1])
	{
		argv[1] = getenv("HOME"); 
	}
	
	if(chdir(argv[1]) < 0)
	{
		char buf[_SIZE_];
		sprintf(buf, "%s: %s: %s\n", argv[0], argv[1], strerror(errno));
		result = buf;
		return 1;
	}
	result = "";
	return 0;
}

int show_builtins(char* argv[])
{
	const char* *cur= builtins;
	result = "";
	for (; NULL != *cur; ++cur)
	{
		result += *cur;
		result += "\n";
	}

	return 0;
}

int do_exit(char *argv[])
{
	return -1;	
}

void add_histroy(std::string &cmd)
{
	if (history.size() == max_history_size)
		history.pop_front();
	history.push_back(cmd);
}

int show_history(char* argv[])
{
	std::list<std::string>::iterator cur = history.begin();
	result = "";
	int i = 1;
	char buf[4];
	while (cur != history.end())
	{
		sprintf(buf, "%d ", i++);
		result += buf;
		result += *cur;
		result += "\n";
		++cur;
	}
	return 0;
}

int do_last(char* argv[])
{
	if (history.empty())
		return 0;
	std::string last("!!");
	return exec_command(last);
}

int do_alias(char* argv[])
{
	// 打印alias
	result = "";
	
	if (argv[1] == NULL)
	{
		std::list<std::string>::iterator pos = alias.begin();
		for (; pos != alias.end(); ++pos)
		{
			result += "alias ";		
			result += *pos;
			result += "\n";
		}
		return  0;
	}

	// 添加alias
	if (alias.size() < max_alias_size)
	{
		char *str = argv[1];
		std::string tmp(str);
		size_t pos;

		if ((pos = tmp.find_first_of("=")) == std::string::npos)
		{
			result = "alias: ";
			result += argv[1];
			result += ": not found\n";
		}
		else
		{
			std::list<std::string>::iterator cur = alias.begin();
			int len = 0;
			char *str = argv[1];
			while (*str != '=')
			{
				len++;
				str++;
			}
			for (; cur != alias.end(); ++cur)
			{
				if (strncmp((*cur).c_str(), argv[1], len) == 0)
				{
					alias.erase(cur);
					break;
				}
			}

			pos++;
			if (tmp[pos] != '\'')
			{
				tmp.insert(pos, "\'");		
				tmp.insert(tmp.size(), "\'");
			}

			for (int i = 2; i < 10; i++)
			{
				if (argv[i] == NULL)
					break;
				else
				{
					tmp.insert(tmp.size() - 2, " ");						
					tmp.insert(tmp.size() - 2, argv[i]);						
				}
			}

			alias.push_back(tmp);
		}
	}
	return 0;
}

// unalias
int do_unalias(char* argv[])
{
	result = "";
	if (NULL == argv[1])
		return 0;

	std::list<std::string>::iterator pos;
	char *cmd = argv[1];
	int len = strlen(cmd);
	cmd[len] = '=';
	cmd[len+1] = '\0';

	for (pos = alias.begin(); pos != alias.end();)
	{
		std::string &str = *pos;
		if (strncmp(str.c_str(), cmd, len) == 0)
		{
			pos = alias.erase(pos);
			break;
		}
		else
			++pos;
	}
	return 0;
}


