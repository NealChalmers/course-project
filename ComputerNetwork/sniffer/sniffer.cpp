#pragma comment(lib,"ws2_32")

#include <winsock2.h>
#include <string.h>
#include <windows.h>
#include <mstcpip.h>
#include <iostream>
#include <stdio.h>
#define RECVPORT 7000     //绑定的接包端口号

struct iphdr
{
	unsigned char head;
	unsigned char tos;
	unsigned short length;     //IP包头定义
	unsigned short flags;
	unsigned short offset;
	unsigned char ttl;
	unsigned char protc;
	unsigned short checksum;
	unsigned int sourceip;
	unsigned int destip;
};

struct udphdr
{
	unsigned int sourceport;
	unsigned int destport;
	unsigned int length;				//UDP包头定义
	unsigned int checksum;
};

struct tcphdr
{
	USHORT sourceport;
	USHORT destport;
	unsigned int seq;
	unsigned int ack;					//TCP包头定义
	unsigned char offset;
	unsigned char flags;
	USHORT win;
	USHORT checksum;
	USHORT urg;
};

FILE *f;
char orig[100], *p, end;
char type[20] = { 0 }, version[20] = { 0 }, plat[20] = { 0 }, ttl[20] = { 0 }, win[20] = { 0 }, df[20] = { 0 }, tos[20] = { 0 };
int i = 0, j = 0;
int ttli, dfi, tosi, winb, wine;
bool winf = false;


int solve(char *buff)          //解包函数定义
{
	struct iphdr *ip;
	struct tcphdr *tcp;
	struct udphdr *udp;
	struct sockaddr_in test1, test2;
	BYTE *datat = NULL, *datau = NULL;

	ip = (struct iphdr*)buff;												//取IP头
	tcp = (struct tcphdr*)(buff + ((ip->head) & 0xf) * sizeof(unsigned int)); //取TCP头
	udp = (struct udphdr*)(buff + ((ip->head) & 0xf) * sizeof(unsigned int)); //取UDP头
	test1.sin_addr.s_addr = ip->sourceip;
	test2.sin_addr.s_addr = ip->destip;
	datat = ((BYTE *)tcp) + (tcp->offset >> 4) * 4;
	datau = (BYTE *)udp;
	printf("从:%s,", inet_ntoa(test1.sin_addr));
	printf("到:%s\n", inet_ntoa(test2.sin_addr));
	switch (ip->protc)
	{
	case 1:printf("Proto ICMP,"); break;
	case 2:printf("Proto IGMP,"); break;
	case 6:printf("Proto TCP,"); break;
	case 8:printf("Proto EGP,"); break;
	case 9:printf("Proto IGP,"); break;
	case 17:printf("Proto UDP,"); break;
	case 41:printf("Proto IPv6,"); break;
	case 89:printf("Proto OSPF,"); break;
	default:printf("Proto error,"); break;
	}
	if (ip->protc == 6)
	{
		int port = 0;
		port = ntohs(tcp->sourceport);
		printf("从TCP端口:%d,到TCP端口:%d,SEQ:%d,ACK:%d\n", ntohs(tcp->sourceport), ntohs(tcp->destport), ntohl(tcp->seq), ntohl(tcp->ack));
		switch (port)
		{
		case 21:printf("这是一个ftp协议数据包\n"); break;
		case 80:printf("这是一个HTTP协议数据包\n"); break;
		case 110:printf("这是一个pop3协议数据包\n"); break;
		case 25:printf("这是一个SMTP协议数据包\n "); break;
		}
		printf("FLAGS:");
		if (tcp->flags & 0x20)
			printf("URG ");
		if (tcp->flags & 0x10)
			printf("ACK ");
		if (tcp->flags & 0x8)                   //对TCP命令，输出标志位
			printf("PSH ");
		if (tcp->flags & 0x4)
			printf("RST ");
		if (tcp->flags & 0x2)
			printf("SYN ");
		if (tcp->flags & 0x1)
			printf("FIN ");
		printf("data:%s\n", datat);

	}
	else if (ip->protc == 17)
	{
		printf("从UDP端口:%d,到UDP端口:%d,\nDATA:%s", ntohs(udp->sourceport), ntohs(udp->destport), datau);
	}
	printf("TTL:%d\n", ip->ttl);
	printf("\n");

	return 0;
}

int main()
{
	WSADATA ws;
	long lresult;
	struct hostent *host;
	char IpAddress[100], buffer[65535];
	int err1, err2, err3, i;

	lresult = WSAStartup(MAKEWORD(2, 2), &ws);
	if (lresult != 0)
		printf("error!");
	if (gethostname(IpAddress, sizeof(IpAddress)) != 0)
		std::cout << "get hostname failed" << std::endl;

	SOCKET sock;
	SOCKADDR_IN myaddress;

	u_long ulDestIP = inet_addr(IpAddress);
	//转换不成功时按域名解析
	if (ulDestIP == INADDR_NONE)
	{
		hostent * pHostent = gethostbyname(IpAddress);
		if (pHostent)
			myaddress.sin_addr = *(in_addr*)pHostent->h_addr_list[0];
	}
	else
		std::cout << "获取主机ip地址失败" << std::endl;

	myaddress.sin_family = AF_INET;
	myaddress.sin_port = htons(RECVPORT);             //initial

	if ((sock = WSASocket(AF_INET, SOCK_RAW, IPPROTO_IP, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)	//create socket
	{
		printf("error:  WSASocket()! error_number:%d", WSAGetLastError());
		return 1;
	}

	err2 = bind(sock, (PSOCKADDR)&myaddress, sizeof(myaddress));   //bind

	if (err2 < 0)
	{
		std::cout << WSAGetLastError() << std::endl;
		exit(1);
	}

	DWORD inbuffer = 1;
	DWORD outbuffer[10];
	DWORD returned = 0;
	err1 = WSAIoctl(sock, SIO_RCVALL, &inbuffer, sizeof(inbuffer), &outbuffer, sizeof(outbuffer), &returned, NULL, NULL);
	if (err1 < 0)
	{
		std::cout << "IO OPTION SET ERROR!" << std::endl;//设置端口为接收所有包模式
		exit(1);
	}
	for (i = 1; i <= 30; i++)
	{
		memset(buffer, 0, sizeof(buffer));//清空接收缓冲区
		err3 = recv(sock, buffer, sizeof(buffer), 0);    //接包
		if (err3 < 0)
		{
			std::cout << "RECEIVE ERROR!" << std::endl;
			exit(1);
		}
		solve(buffer);          //定义解包函数解包
	}
	return 0;
}