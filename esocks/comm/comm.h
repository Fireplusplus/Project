#pragma once

int recv_n(int sock, char *buf, int len);

int send_n(int sock, char *buf, int len);

void encryption(char *buf, int len);
