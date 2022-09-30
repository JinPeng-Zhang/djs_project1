#include<stdio.h>
#include<winsock.h>
#include<string.h>
#include <time.h>

bool creatscoket(char *ip,int port);
int str_2ip_port(char* str, char** ip, int* port);
int time();
int main(int argc,char **argv) {

	char* ip;
	int port;
	if(argc==2 && !str_2ip_port(argv[1], &ip, &port))
	creatscoket(ip,port);

	return 0;
}
bool creatscoket(char *ip,int port) {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		printf("WSAStartup() error!");

	 SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	 SOCKET new_s;
	 struct sockaddr_in saddr,new_addr;

	 memset(&saddr, 0, sizeof(saddr));
	 saddr.sin_family = AF_INET;
	 saddr.sin_addr.s_addr = inet_addr(ip);
	 saddr.sin_port = htons(port);
	 int b = bind(s, (struct sockaddr*)&saddr, sizeof(saddr));

	 if (listen(s, 5) == SOCKET_ERROR)
		 printf("error");
	 int szClntAddr = sizeof(new_addr);
	 new_s = accept(s, (SOCKADDR*)&new_addr, &szClntAddr);

	 char message[] = "Hello World!";
	 send(new_s, message, sizeof(message), 0);

		// ErrorHandling("listen() error");
     return false;
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
	printf("ip :%s\nport :%d\n", *ip,  *port);
	return 0;
}

int time()
{
	char point = '.';
	//获取秒
	time_t tt;
	time(&tt);
	char* s = (char *)malloc(sizeof(char)*10);
	itoa((int)tt,s,10);
	//获取毫秒
	SYSTEMTIME t1;
	GetSystemTime(&t1);
	char* ms = (char*)malloc(sizeof(char) * 3);
	itoa((int)t1.wMilliseconds, ms, 10);

	strcat(s, ".");
	strcat(s, ms);

	return strlen(s);
}