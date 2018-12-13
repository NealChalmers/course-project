/* client code */

#pragma comment(lib,"ws2_32")

#include <stdio.h>
#include <Winsock2.h>
#include <iostream>

int main()
{
	WORD wVersionRequested;
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

	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);				//get socket
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));			//connect server
	std::cout << inet_ntoa(addrSrv.sin_addr) << std::endl;
	char sendBuf[50];

	while (1)
	{
		sendBuf[0] = '\0';
		if (std::cin.getline(sendBuf, 50))
			send(sockClient, sendBuf, strlen(sendBuf) + 1, 0);
	}

	closesocket(sockClient);
	WSACleanup();
}