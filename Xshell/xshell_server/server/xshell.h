#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include "data.h"

#define _SIZE_ 1024

extern std::string result;

int init(const char *ip, short port);

void get_cmd_line(std::string &out);

void sending(int _fd, const std::string &in);

int recving(int fd, std::string &out);

void my_popen(std::string &cmd_rs);


int exec_command(std::string &cmd_rs);

void command_format(std::string &in, char* out[]);

int change_dir(char* argv[]);

int show_builtins(char* argv[]);

int do_exit(char* argv[]);

void add_histroy(std::string &cmd);

int show_history(char* argv[]);

int do_last(char* argv[]);

int do_alias(char* argv[]);

int do_unalias(char* argv[]);




