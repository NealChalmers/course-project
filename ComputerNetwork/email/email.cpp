#pragma comment(lib, "Ws2_32.lib")

#include "sock.h" 
#include <iostream> 
#include <winsock.h>

const int MAX_PACKET_SIZE = 1024;//报文最大长度（包括报头）

int main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		std::cout << "startup failed" << std::endl;

	char IpAddress[255];//获取本机IP
	if (gethostname(IpAddress, sizeof(IpAddress)) != 0)
		std::cout << "获取主机名失败" << std::endl;
	//cout << "请输入一个IP地址或域名：";
	//得到IP 地址
	u_long ulDestIP = inet_addr(IpAddress);
	//转换不成功时按域名解析
	if (ulDestIP == INADDR_NONE)
	{
		hostent * pHostent = gethostbyname(IpAddress);
		if (pHostent)
			ulDestIP = (*(in_addr*)pHostent->h_addr).s_addr;
	}
	else
		std::cout << "获取主机ip地址失败" << std::endl;

	//填充目地端socket地址
	sockaddr_in destSockAddr;
	ZeroMemory(&destSockAddr, sizeof(sockaddr_in));
	destSockAddr.sin_family = AF_INET;
	destSockAddr.sin_port = htons(25);//端口设置
	hostent* hptr = gethostbyname("smtp.163.com");
	memcpy(&destSockAddr.sin_addr.S_un.S_addr, hptr->h_addr_list[0], hptr->h_length);//邮件服务器地址

	//创建原始套接字
	SOCKET sockRaw = socket(PF_INET, SOCK_STREAM, 0);

	char recvBuf[10240];

	int port = 25;//smtp协议专用端口 
	char wkstr[100] = "hello,how are you?";//邮件内容 
	if (connect(sockRaw, (SOCKADDR*)&destSockAddr, sizeof(SOCKADDR)))
		return 1;
	int bend = recv(sockRaw, recvBuf, MAX_PACKET_SIZE, 0);
	recvBuf[bend] = '\0';
	std::cout << "Client : connected! \nServer :" << recvBuf << std::endl;

	send(sockRaw, "EHLO NjQxOTIwMDA0QHFxLmNvbQ==\r\n", MAX_PACKET_SIZE, 0);
	bend = recv(sockRaw, recvBuf, MAX_PACKET_SIZE, 0);
	recvBuf[bend] = '\0';

	/* EHLO指令是必须首先发的，相当于和服务器说hello */
	/*sock.send_socket("EHLO **********\r\n");//邮箱用户名
	sock.recv_socket();*/
	std::cout << "Client : send helo \nServer :"
		<< recvBuf << std::endl;

	send(sockRaw, "AUTH LOGIN\r\n", MAX_PACKET_SIZE, 0);
	bend = recv(sockRaw, recvBuf, MAX_PACKET_SIZE, 0);
	std::cout << bend << std::endl;
	recvBuf[bend] = '\0';

	/*发送 auth login 指令，告诉服务器要登录邮箱*/
	/*sock.send_socket("auth login\r\n");
	sock.recv_socket();*/
	std::cout << "Client : send auth login \nServer :"
		<< recvBuf << std::endl;

	/*告诉服务器要登录后，接着就是把用户名发过去了.
	不过这个用户名是经过了base64编码的，smtp也支持
	明文传送，至于具体有什么区别上网上找资料看看就知道了*/
	/*sock.send_socket("**********");//经过base64编码后的邮箱用户名
	sock.send_socket("\r\n");
	sock.recv_socket();*/

	send(sockRaw, "Y2hhbG1lcnMxMTFAcXEuY29t", MAX_PACKET_SIZE, 0);
	send(sockRaw, "\r\n", MAX_PACKET_SIZE, 0);
	bend = recv(sockRaw, recvBuf, MAX_PACKET_SIZE, 0);
	recvBuf[bend] = '\0';

	std::cout << "Client : send name \nServer :"
		<< recvBuf << std::endl;

	/* 用户名发过去后接着就是用户密码了，当然也是经过base64编码后的*/
	/*sock.send_socket("base64编码后的密码");
	sock.send_socket("\r\n");
	sock.recv_socket();*/

	send(sockRaw, "********", MAX_PACKET_SIZE, 0);//email password
	send(sockRaw, "\r\n", MAX_PACKET_SIZE, 0);
	bend = recv(sockRaw, recvBuf, MAX_PACKET_SIZE, 0);
	recvBuf[bend] = '\0';

	std::cout << "Client : send password \nServer :"
		<< recvBuf << std::endl;

	/*发送 mail from 指令，相当于填写发件人*/
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

	/*发送 rcpt to 指令，就是填写收件人了 */
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

	/*发送data,标志着后面开始发送邮件的主题部分*/
	/*sock.send_socket("data\r\n");
	sock.recv_socket();*/

	send(sockRaw, "data\r\n", MAX_PACKET_SIZE, 0);
	bend = recv(sockRaw, recvBuf, MAX_PACKET_SIZE, 0);
	recvBuf[bend] = '\0';

	std::cout << "Client : send data \nServer :"
		<< recvBuf << std::endl;

	/*发送邮件主体部分，先是邮件主题（subject）,后面是邮件内容。
	下面就是发送主体的格式*/
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
