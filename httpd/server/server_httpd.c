#include "server_httpd.h"

void not_found(int sock)
{
	char buf[_SIZE_];
	sprintf(buf, "HTTP/1.0 404 NOT FOUND\r\n");
	send(sock, buf, strlen(buf), 0);
	sprintf(buf, "Content-Type: text/html\r\n\r\n");
	send(sock, buf, strlen(buf), 0);
	sprintf(buf, "<html><h1>NOT FOUND!</h1></html>");
	send(sock, buf, strlen(buf), 0);
}

void echo_errno(int sock, int num)
{
	switch(num)
	{
	case 404:
		not_found(sock);
		break;
	case 401:
		break;
	case 400:
		break;
	case 500:
		break;
	case 503:
		break;
	}

	close(sock);
}

int start_up(const char* ip, int port)
{
	assert(NULL != ip);
	assert(port > 0);

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		perror("socket");
		exit(1);
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);
	if (bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0)
	{
		perror("bind");
		exit(2);
	}

	if (listen(sock, 5) < 0)
	{
		perror("listen");
		exit(3);
	}

	return sock;
}

void usage(const char* proc)
{
	assert(NULL != proc);

	printf("Usage: %s [ip] [port]\n", proc);
}

int get_line(int sock, char* buf, size_t size)
{
	assert(buf);

	int ch = 0;
	int i = 0;
	while (i < size && ch != '\n')
	{
		ssize_t s = recv(sock, &ch, 1, 0);
		if (s < 0)
		{
			perror("recv");
		}
		else if (s == 0)
		{
			printf("client closed...\n");
			close(sock);
			break;
		}
		else
		{
			if (ch == '\r')
			{
				recv(sock, &ch, 1, MSG_PEEK);
				if (ch != '\n')
					ch = '\n';
				else
					recv(sock, &ch, 1, 0);
			}
			buf[i++] = ch;
		}
	}
	buf[i] = '\0';
	return i;
}

void clear_header(int sock)
{
	int ret = 0;
	char buf[_SIZE_];
	do
	{
		ret = get_line(sock, buf, sizeof(buf)-1);
	} while (ret > 0 && strcmp(buf, "\n") != 0);
}

void echo_www(int sock, char* path, ssize_t size)
{
	printf("echo_www\n");
	int fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		echo_errno(sock, 404);
		return;
	}

	char buf[_SIZE_];
	sprintf(buf, "HTTP/1.0 200 OK \r\n\r\n");
	// write
	send(sock, buf, strlen(buf), 0);
	if (sendfile(sock, fd, NULL, size) < 0)
	{
		echo_errno(sock, 404);
		return;
	}
	close(sock);
}

void exec_cgi(int sock, const char* method, const char* path, const char* query_string)
{
	char buf[_SIZE_];
	int ret = 0;
	int content_len = -1;
	char method_env[_SIZE_];
	char query_string_env[_SIZE_];
	char content_len_env[_SIZE_];

	if (strcasecmp(method, "GET") == 0)
	{
		clear_header(sock);
	}
	else
	{
		do
		{
			ret = get_line(sock, buf, sizeof(buf)-1);
			if (ret > 0 && strncasecmp(buf, "Content-Length: ", 16) == 0)
			{
				content_len = atoi(buf+16);
			}
		} while (ret > 0 && strcasecmp(buf, "\n") != 0);
		if (content_len == -1)
		{
			echo_errno(sock, 404);
			return;
		}
	}

	int input[2];
	int output[2];
	if (pipe(input) < 0)
	{
		echo_errno(sock, 404);
		return;
	}

	if (pipe(output) < 0)
	{
		echo_errno(sock, 404);
		return;
	}

	pid_t id = fork();
	if (id == 0)	// child
	{
		close(input[1]);	
		close(output[0]);	
		dup2(input[0], 0);
		dup2(output[1], 1);

		sprintf(method_env, "METHOD=%s", method);
		putenv(method_env);
		if (strcasecmp(method, "GET") == 0)
		{
			sprintf(query_string_env, "QUERY_STRING=%s", query_string);
			putenv(query_string_env);
		}
		else
		{
			sprintf(content_len_env, "CONTENT_LENGTH=%d", content_len);
			putenv(content_len_env);
		}
		
		execl(path, path, NULL);
		exit(1);
	}
	else	// father
	{
		close(input[0]);	
		close(output[1]);	
		int i = 0;
		int ch = 0;

		if (strcasecmp(method, "POST") == 0)
		{
			for (; i < content_len; i++)
			{
				recv(sock, &ch, 1, 0);
				write(input[1], &ch, 1);
			}
		}
		while (read(output[0], &ch, 1) > 0)
		{
			send(sock, &ch, 1, 0);
		}
		waitpid(id, NULL, 0);

	}

	return;
}

void* accept_request(void* argc)
{
	int sock = (int)argc;
	
	char line[_SIZE_];
	char method[_SIZE_];
	char url[_SIZE_];
	char path[_SIZE_];
	int i = 0, j = 0;
	int cgi = 0;
	char* query_string = NULL;

#ifdef _DEBUG_
	char buf[10240];
	ssize_t s;
	if ((s = read(sock, buf, sizeof(buf)-1)) > 0)
	{
		buf[s] = 0;
		printf("%s", buf);
	}
#endif

	int len = get_line(sock, line, sizeof(line)-1);
	printf("%d : %s", len, line);

	while (i < sizeof(method)-1 && j < sizeof(line) && !isspace(line[j]))
	{
		method[i++] = line[j++];;
	}
	method[i] = 0;

	while (j < sizeof(line) && isspace(line[j]))
	{
		j++;
	}

	i=0;
	while (i < sizeof(url)-1 && j < sizeof(line) && !isspace(line[j]))
	{
		url[i++] = line[j++];
	}
	url[i] = 0;

	printf("method: %s\n", method);
	printf("url: %s\n", url);

	if (strcasecmp(method, "POST") != 0 && strcasecmp(method, "GET") != 0)
	{
		echo_errno(sock, 404);
		return (void*)-1;
	}

	if (strcasecmp(method, "POST") == 0)
	{
		cgi = 1;
	}

	if (strcasecmp(method, "GET") == 0)
	{
		query_string = url;
		while (*query_string != '\0')
		{
			if (*query_string == '?')
			{
				cgi = 1;
				*query_string = '\0';
				query_string++;
				break;
			}
			query_string++;
		}
	}

	// url, query_string
	sprintf(path, "htdocs%s", url);
	if (path[strlen(path)-1] == '/')
	{
		strcat(path, "index.html");
	}

	printf("path: %s\n", path);
	
	// path
	struct stat st;
	if (stat(path, &st) < 0)
	{
		echo_errno(sock, 404);
		return (void*)-2;
	}
	else
	{
		if (S_ISDIR(st.st_mode))
		{
			strcat(path, "index.html");
		}
		else if ((st.st_mode & S_IXUSR) || (st.st_mode & S_IXGRP) || (st.st_mode & S_IXOTH))
		{
			cgi = 1;
		}

		if (cgi)
		{
			exec_cgi(sock, method, path, query_string);
		}
		else
		{
			clear_header(sock);
			echo_www(sock, path, st.st_size);
		}
	}
	close(sock);
	return (void*)0;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		usage(argv[0]);
		return 4;
	}

	int listen_sock = start_up(argv[1], atoi(argv[2]));

	while (1)
	{
		struct sockaddr_in client;
		socklen_t len = sizeof(client);
		int new_fd = accept(listen_sock, (struct sockaddr*)&client, &len);
		if (new_fd < 0)
		{
			perror("accept");
			continue;
		}
		
		pthread_t id;
		pthread_create(&id, NULL, accept_request, (void*)new_fd);
		pthread_detach(id);
	}

	return 0;
}




















