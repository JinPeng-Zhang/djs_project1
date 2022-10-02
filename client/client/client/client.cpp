#include<stdio.h>
#include<winsock.h>
#include <time.h>
//消息长度最大值
#define mess_max 512

int str_2ip_port(char* str, char** ip, int* port);
void get_time(struct timer* t);
struct timer {
	time_t second;
	WORD millisecond;
};
int main(int argc,char* argv[]) {
	if (argc!=2) return 0;
	char* ip;int port;
	int cnt = 30;
	if (str_2ip_port(argv[1], &ip, &port))
		return 0;
	//windows启动socket服务
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		printf("WSAStartup() error!\n");

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	SOCKET new_s;
	struct sockaddr_in saddr, new_addr;
	struct timer t;

	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = inet_addr(ip);
	saddr.sin_port = htons(port);

	if (connect(s, (SOCKADDR*)&saddr, sizeof(saddr)) == -1) {
		printf("connect feiled\n");
		return 0;
	}
	char* message = (char*)malloc(sizeof(char) * 20);
	while (cnt--) {
		recv(s, message, 20, 0);
		get_time(&t);
		send(s, message, strlen(message) + 1, 0);
		printf("Message from server: %s at %d:%d\n", message, t.second, t.millisecond);
	}
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

void get_time(struct timer* t)
{
	time(&(t->second));
	SYSTEMTIME t1;
	GetSystemTime(&t1);
	t->millisecond = t1.wMilliseconds;

}