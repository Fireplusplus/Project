#pragma once
#pragma comment(lib,"ws2_32.lib")

#include <Winsock2.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <windows.h>
#include "json\json.h"
#include "data.h"

#define _SIZE_ 2048

SOCKET init(const char *_ip, short _port);

void recving(int sock, std::string &out);

void sending(int sock, std::string &in);

