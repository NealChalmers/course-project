#pragma comment(lib, "Ws2_32.lib")

#include "sock.h" 
#include <iostream> 
#include <winsock.h>

const int MAX_PACKET_SIZE = 1024;//������󳤶ȣ�������ͷ��

int main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		std::cout << "startup failed" << std::endl;

	char IpAddress[255];//��ȡ����IP
	if (gethostname(IpAddress, sizeof(IpAddress)) != 0)
		std::cout << "��ȡ������ʧ��" << std::endl;
	//cout << "������һ��IP��ַ��������";
	//�õ�IP ��ַ
	u_long ulDestIP = inet_addr(IpAddress);
	//ת�����ɹ�ʱ����������
	if (ulDestIP == INADDR_NONE)
	{
		hostent * pHostent = gethostbyname(IpAddress);
		if (pHostent)
			ulDestIP = (*(in_addr*)pHostent->h_addr).s_addr;
	}
	else
		std::cout << "��ȡ����ip��ַʧ��" << std::endl;

	//���Ŀ�ض�socket��ַ
	sockaddr_in destSockAddr;
	ZeroMemory(&destSockAddr, sizeof(sockaddr_in));
	destSockAddr.sin_family = AF_INET;
	destSockAddr.sin_port = htons(25);//�˿�����
	hostent* hptr = gethostbyname("smtp.163.com");
	memcpy(&destSockAddr.sin_addr.S_un.S_addr, hptr->h_addr_list[0], hptr->h_length);//�ʼ���������ַ

	//����ԭʼ�׽���
	SOCKET sockRaw = socket(PF_INET, SOCK_STREAM, 0);

	char recvBuf[10240];

	int port = 25;//smtpЭ��ר�ö˿� 
	char wkstr[100] = "hello,how are you?";//�ʼ����� 
	if (connect(sockRaw, (SOCKADDR*)&destSockAddr, sizeof(SOCKADDR)))
		return 1;
	int bend = recv(sockRaw, recvBuf, MAX_PACKET_SIZE, 0);
	recvBuf[bend] = '\0';
	std::cout << "Client : connected! \nServer :" << recvBuf << std::endl;

	send(sockRaw, "EHLO NjQxOTIwMDA0QHFxLmNvbQ==\r\n", MAX_PACKET_SIZE, 0);
	bend = recv(sockRaw, recvBuf, MAX_PACKET_SIZE, 0);
	recvBuf[bend] = '\0';

	/* EHLOָ���Ǳ������ȷ��ģ��൱�ںͷ�����˵hello */
	/*sock.send_socket("EHLO **********\r\n");//�����û���
	sock.recv_socket();*/
	std::cout << "Client : send helo \nServer :"
		<< recvBuf << std::endl;

	send(sockRaw, "AUTH LOGIN\r\n", MAX_PACKET_SIZE, 0);
	bend = recv(sockRaw, recvBuf, MAX_PACKET_SIZE, 0);
	std::cout << bend << std::endl;
	recvBuf[bend] = '\0';

	/*���� auth login ָ����߷�����Ҫ��¼����*/
	/*sock.send_socket("auth login\r\n");
	sock.recv_socket();*/
	std::cout << "Client : send auth login \nServer :"
		<< recvBuf << std::endl;

	/*���߷�����Ҫ��¼�󣬽��ž��ǰ��û�������ȥ��.
	��������û����Ǿ�����base64����ģ�smtpҲ֧��
	���Ĵ��ͣ����ھ�����ʲô���������������Ͽ�����֪����*/
	/*sock.send_socket("**********");//����base64�����������û���
	sock.send_socket("\r\n");
	sock.recv_socket();*/

	send(sockRaw, "Y2hhbG1lcnMxMTFAcXEuY29t", MAX_PACKET_SIZE, 0);
	send(sockRaw, "\r\n", MAX_PACKET_SIZE, 0);
	bend = recv(sockRaw, recvBuf, MAX_PACKET_SIZE, 0);
	recvBuf[bend] = '\0';

	std::cout << "Client : send name \nServer :"
		<< recvBuf << std::endl;

	/* �û�������ȥ����ž����û������ˣ���ȻҲ�Ǿ���base64������*/
	/*sock.send_socket("base64����������");
	sock.send_socket("\r\n");
	sock.recv_socket();*/

	send(sockRaw, "********", MAX_PACKET_SIZE, 0);//email password
	send(sockRaw, "\r\n", MAX_PACKET_SIZE, 0);
	bend = recv(sockRaw, recvBuf, MAX_PACKET_SIZE, 0);
	recvBuf[bend] = '\0';

	std::cout << "Client : send password \nServer :"
		<< recvBuf << std::endl;

	/*���� mail from ָ��൱����д������*/
	/*sock.send_socket("mail from: <");
	sock.send_socket("yuzhenxiong0823@126.com");
	sock.send_socket(">");
	sock.send_socket("\r\n");
	sock.recv_socket();*/

	send(sockRaw, "mail from: <", MAX_PACKET_SIZE, 0);
	send(sockRaw, "yuzhenxiong0823@qq.com", MAX_PACKET_SIZE, 0);
	send(sockRaw, ">", MAX_PACKET_SIZE, 0);
	send(sockRaw, "\r\n", MAX_PACKET_SIZE, 0);
	bend = recv(sockRaw, recvBuf, MAX_PACKET_SIZE, 0);
	recvBuf[bend] = '\0';

	std::cout << "Client: send mail from \nServer :"
		<< recvBuf << std::endl;

	/*���� rcpt to ָ�������д�ռ����� */
	/*sock.send_socket("rcpt to: <");
	sock.send_socket("120091241@qq.com");
	sock.send_socket(">");
	sock.send_socket("\r\n");
	sock.recv_socket();*/

	send(sockRaw, "rcpt to: ", MAX_PACKET_SIZE, 0);
	send(sockRaw, "neal.cai@hotmail.com", MAX_PACKET_SIZE, 0);
	send(sockRaw, ">", MAX_PACKET_SIZE, 0);
	send(sockRaw, "\r\n", MAX_PACKET_SIZE, 0);
	bend = recv(sockRaw, recvBuf, MAX_PACKET_SIZE, 0);
	recvBuf[bend] = '\0';

	std::cout << "Client : send rcpt to \nServer"
		<< recvBuf << std::endl;

	/*����data,��־�ź��濪ʼ�����ʼ������ⲿ��*/
	/*sock.send_socket("data\r\n");
	sock.recv_socket();*/

	send(sockRaw, "data\r\n", MAX_PACKET_SIZE, 0);
	bend = recv(sockRaw, recvBuf, MAX_PACKET_SIZE, 0);
	recvBuf[bend] = '\0';

	std::cout << "Client : send data \nServer :"
		<< recvBuf << std::endl;

	/*�����ʼ����岿�֣������ʼ����⣨subject��,�������ʼ����ݡ�
	������Ƿ�������ĸ�ʽ*/
	/*sock.send_socket("subject:");
	sock.send_socket("testmail\r\n");
	sock.send_socket("\r\n\r\n");
	sock.send_socket("hello,how are you.\r\n");
	sock.send_socket(".\r\n");
	sock.recv_socket();*/

	send(sockRaw, "subject:", MAX_PACKET_SIZE, 0);
	send(sockRaw, "testmail\r\n", MAX_PACKET_SIZE, 0);
	send(sockRaw, "\r\n\r\n", MAX_PACKET_SIZE, 0);
	send(sockRaw, "hello,how are you.\r\n", MAX_PACKET_SIZE, 0);
	send(sockRaw, ".\r\n", MAX_PACKET_SIZE, 0);
	bend = recv(sockRaw, recvBuf, MAX_PACKET_SIZE, 0);
	recvBuf[bend] = '\0';

	std::cout << "Client : send content \nServer :"
		<< recvBuf << std::endl;

	/*sock.send_socket("quit\r\n");
	sock.recv_socket();*/

	send(sockRaw, "quit\r\n:", MAX_PACKET_SIZE, 0);
	bend = recv(sockRaw, recvBuf, MAX_PACKET_SIZE, 0);
	recvBuf[bend] = '\0';

	std::cout << "Client : send quit \nServer :"
		<< recvBuf << std::endl;

}
