#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/sendfile.h>


#define _SIZE_ 1024


void echo_errno(int sock, int num);

int start_up(const char* ip, int port);

int get_line(int sock, char* buf, size_t size);

void* accept_request(void* argc);

void usage(const char* proc);

void clear_header(int sock);

void echo_www(int sock, char* path, ssize_t size);

void exec_cgi(int sock, const char* method, const char* path, const char* query_string);

