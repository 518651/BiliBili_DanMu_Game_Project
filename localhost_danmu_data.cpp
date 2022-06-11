#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include "Control.h"
#include <stdio.h>
#include <stdlib.h>
#include<cstring>
#include<WS2tcpip.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll

DanMu_Data DanMu_Data_L;



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


	//	3	绑定套接字	指定绑定的IP地址和端口号b
	sockaddr_in socketAddr;
	socketAddr.sin_family = PF_INET;
	socketAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//127.0.0.1  192.168.3.74
	socketAddr.sin_port = htons(5555);
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
		char recvBuf[4028] = {};
		recv(clientSocket, recvBuf, 4028, 0);
		//cout<< UTF8ToGBK(recvBuf) << endl << endl;
		//danmu_funtion_data = recvBuf;
		cotrol_Thread(python_data_analysis(UTF8ToGBK(recvBuf)));
		//cotrol_Thread(recvBuf);
	}
	//	6	关闭socket
	closesocket(clientSocket);


	//	7	终止
	WSACleanup();

	cout << "客户端退出" << endl;
	cin.get();
}


