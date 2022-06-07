﻿#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include "Control.h"
#include <stdio.h>
#include <stdlib.h>
#include<cstring>
#include<WS2tcpip.h>
#include <WinSock2.h>
#include<Windows.h>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll
using namespace std;

void Get_Data_Page_Information()
{
	cout << "-----------客户端-----------" << endl;

	//	1	初始化
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);


	//	2	创建套接字
	SOCKET clientSocket = {};
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == clientSocket) {
		cout << "套接字闯创建失败!" << endl;
	}
	else {
		cout << "套接字创建成功!" << endl;
	}


	//	3	绑定套接字	指定绑定的IP地址和端口号
	sockaddr_in socketAddr;
	socketAddr.sin_family = PF_INET;
	socketAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	socketAddr.sin_port = htons(33333);
	int cRes = connect(clientSocket, (SOCKADDR*)&socketAddr, sizeof(SOCKADDR));
	if (SOCKET_ERROR == cRes) {
		cout << "客户端:\t\t与服务器连接失败....." << endl;
	}
	else {
		cout << "客户端:\t\t与服务器连接成功....." << endl;
	}

	while (true)
	{
		//	5	发送/接受 数据
		char recvBuf[1024] = {};
		recv(clientSocket, recvBuf, 1024, 0);
		cout<< UTF8ToGBK(recvBuf) << endl << endl;
	}
	//	6	关闭socket
	closesocket(clientSocket);


	//	7	终止
	WSACleanup();

	cout << "客户端退出" << endl;
	cin.get();
}


