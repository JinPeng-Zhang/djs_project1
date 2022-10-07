#include<stdio.h>
#include<winsock.h>
#include<string.h>
#include <time.h>

int str_2ip_port(char* str, char** ip, int* port);
void get_time(struct timer *t);
//��һ��timer�ṹ��ת��Ϊ ��second.txt���ַ���
char* get_delayfile_path(char* s, struct timer t);
//��ʱ�����������·��,����ڡ�����ִ���ļ��С�
char delay_file_path[] = "../delay/";
struct timer {
	time_t second;
	WORD millisecond;
};

/*
* ʵ��������Ҫ�ǰ󶨺��׽��֣�Ȼ������Ϣ���ȴ�������Ϣ
*/
int main(int argc,char **argv) {
	struct timer ttime;
	
	
	char* ip;int port;
	int cnt = 30;//���ʹ���
	if (argc >1 && !str_2ip_port(argv[1], &ip, &port))
	{

		//windows���� socket����
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
			printf("WSAStartup() error!");
		//����ʹ�õ���TCP����ͨ�ţ�SOCK_DGRAMΪUDP
		SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
		SOCKET new_s;
		struct sockaddr_in saddr, new_addr;

		memset(&saddr, 0, sizeof(saddr));
		saddr.sin_family = AF_INET;
		saddr.sin_addr.s_addr = inet_addr(ip);
		saddr.sin_port = htons(port);

		int b = bind(s, (struct sockaddr*)&saddr, sizeof(saddr));
			if (b == SOCKET_ERROR) {
				printf("SOCKET_ERROR\n");
				return 0;
			}
			else
				printf("bind %s:%d success\n", ip, port);

		if (listen(s, 5) == SOCKET_ERROR)
			printf("error");
		int szClntAddr = sizeof(new_addr);
		new_s = accept(s, (SOCKADDR*)&new_addr, &szClntAddr);

		if (new_s == -1) {
			printf("accept feiled\n");
			return 0;
		}


		//���ļ���¼30��ͨ����Ϣ
		get_time(&ttime);
		char* file = (char*)malloc(sizeof(char) * 12);
		get_delayfile_path(file, ttime);
		FILE* f = fopen(file, "w");
		if (f == NULL) { printf("file feiled\n"); return 0; }

		char message[] = "Hello World!";
		char* recvmess = (char*)malloc(sizeof(message));
		//message[0] = 0x36;
		while (cnt--) {
			get_time(&ttime);
			fprintf(f, "%d:%d||", ttime.second, ttime.millisecond);
			send(new_s, message, sizeof(message), 0);
			printf("i send:%s at %d:%d and", message, ttime.second, ttime.millisecond);
			recv(new_s, recvmess, 20, 0);
			//Sleep(1);
			get_time(&ttime);
			fprintf(f, "%d:%d\n", ttime.second, ttime.millisecond);
			printf("i recv:%s at %d:%d\n", recvmess, ttime.second, ttime.millisecond);
		}
		fclose(f);
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
	printf("ip :%s\nport :%d\n", *ip,  *port);
	return 0;
}

void get_time(struct timer *t)
{
	time(&(t->second));
	SYSTEMTIME t1;
	GetSystemTime(&t1);
	t->millisecond = t1.wMilliseconds;

}
char* get_delayfile_path(char *s,struct timer t) {
	char* file_name = (char*)malloc(sizeof(char) * 10);
	itoa((int)t.second,file_name, 10);
	strcat(file_name, ".txt");
	*s = '\0';
	strcpy(s, delay_file_path);
	strcat(s, file_name);
	return s;
}