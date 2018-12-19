#pragma comment(lib,"ws2_32")

#include <winsock2.h>
#include <string.h>
#include <windows.h>
#include <mstcpip.h>
#include <iostream>
#include <stdio.h>
#define RECVPORT 7000     //�󶨵ĽӰ��˿ں�

struct iphdr
{
	unsigned char head;
	unsigned char tos;
	unsigned short length;     //IP��ͷ����
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
	unsigned int length;				//UDP��ͷ����
	unsigned int checksum;
};

struct tcphdr
{
	USHORT sourceport;
	USHORT destport;
	unsigned int seq;
	unsigned int ack;					//TCP��ͷ����
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


int solve(char *buff)          //�����������
{
	struct iphdr *ip;
	struct tcphdr *tcp;
	struct udphdr *udp;
	struct sockaddr_in test1, test2;
	BYTE *datat = NULL, *datau = NULL;

	ip = (struct iphdr*)buff;												//ȡIPͷ
	tcp = (struct tcphdr*)(buff + ((ip->head) & 0xf) * sizeof(unsigned int)); //ȡTCPͷ
	udp = (struct udphdr*)(buff + ((ip->head) & 0xf) * sizeof(unsigned int)); //ȡUDPͷ
	test1.sin_addr.s_addr = ip->sourceip;
	test2.sin_addr.s_addr = ip->destip;
	datat = ((BYTE *)tcp) + (tcp->offset >> 4) * 4;
	datau = (BYTE *)udp;
	printf("��:%s,", inet_ntoa(test1.sin_addr));
	printf("��:%s\n", inet_ntoa(test2.sin_addr));
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
		printf("��TCP�˿�:%d,��TCP�˿�:%d,SEQ:%d,ACK:%d\n", ntohs(tcp->sourceport), ntohs(tcp->destport), ntohl(tcp->seq), ntohl(tcp->ack));
		switch (port)
		{
		case 21:printf("����һ��ftpЭ�����ݰ�\n"); break;
		case 80:printf("����һ��HTTPЭ�����ݰ�\n"); break;
		case 110:printf("����һ��pop3Э�����ݰ�\n"); break;
		case 25:printf("����һ��SMTPЭ�����ݰ�\n "); break;
		}
		printf("FLAGS:");
		if (tcp->flags & 0x20)
			printf("URG ");
		if (tcp->flags & 0x10)
			printf("ACK ");
		if (tcp->flags & 0x8)                   //��TCP��������־λ
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
		printf("��UDP�˿�:%d,��UDP�˿�:%d,\nDATA:%s", ntohs(udp->sourceport), ntohs(udp->destport), datau);
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
	//ת�����ɹ�ʱ����������
	if (ulDestIP == INADDR_NONE)
	{
		hostent * pHostent = gethostbyname(IpAddress);
		if (pHostent)
			myaddress.sin_addr = *(in_addr*)pHostent->h_addr_list[0];
	}
	else
		std::cout << "��ȡ����ip��ַʧ��" << std::endl;

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
		std::cout << "IO OPTION SET ERROR!" << std::endl;//���ö˿�Ϊ�������а�ģʽ
		exit(1);
	}
	for (i = 1; i <= 30; i++)
	{
		memset(buffer, 0, sizeof(buffer));//��ս��ջ�����
		err3 = recv(sock, buffer, sizeof(buffer), 0);    //�Ӱ�
		if (err3 < 0)
		{
			std::cout << "RECEIVE ERROR!" << std::endl;
			exit(1);
		}
		solve(buffer);          //�������������
	}
	return 0;
}