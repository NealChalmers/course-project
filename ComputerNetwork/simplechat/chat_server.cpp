/* server code */

#pragma comment(lib,"ws2_32")

#include <stdio.h>
#include <Winsock2.h>
#include <iostream>
#include <string>
#include <thread>

void getClient(SOCKADDR_IN addrClient, SOCKET sockConn);

int main()
{
	WORD wVersionRequested;				// version
	WSADATA wsaData;					
	int err;
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);

	if (err != 0)
	{
		return 0;
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return 0;
	}

	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);			//create socket
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));		//bind socket
	listen(sockSrv, 5);											//set listen
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	SOCKET sockConn;

	while ((sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len)) >= 0)			//get socket
	{
		std::thread thre(getClient, addrClient, sockConn);							//join chat
		thre.detach();
	}
}

void getClient(SOCKADDR_IN addrClient, SOCKET sockConn)
{
	std::string add_s(inet_ntoa(addrClient.sin_addr));
	std::cout << "Welcome " + add_s + " to here!" << std::endl;
	char recvBuf[50];

	while (recv(sockConn, recvBuf, 50, 0) > 0)
	{
		std::cout << add_s << " : " << recvBuf << std::endl;
		recvBuf[0] = '\0';
	}

	closesocket(sockConn);
}