#include<stdio.h>

#include<winsock.h>
int str_2ip_port(char* str, char** ip, int* port);
int main(int argc,char* argv[]) {
	if (argc!=2)
	{
		return 0;
	}
	char* ip;
	int port;
	if (str_2ip_port(argv[1], &ip, &port))
		return 0;
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		printf("WSAStartup() error!");

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	SOCKET new_s;
	struct sockaddr_in saddr, new_addr;

	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	saddr.sin_port = htons(1234);
	connect(s, (SOCKADDR*)&saddr, sizeof(saddr));

	char message[30];
	recv(s, message, sizeof(message) - 1, 0);
	printf("Message from server: %s \n", message);
	return 0;
}
int str_2ip_port(char* str, char** ip, int* port) {
	if (str == NULL) return -1;
	*ip = str;
	char* i = strchr(*ip, ':');
	if (i == NULL)
		return -1;
	i[0] = '\0';
	i = i + 1;
	*port = atoi(i);
	printf("ip :%s\nport :%d\n", *ip, *port);
	return 0;
}


