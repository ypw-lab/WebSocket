#include "XTcp.h"
#include<windows.h>
#include<iostream>
#include<thread>



XTcp::XTcp() {
	static bool first = true;
	if (first) {
		first = false;
		WSADATA ws;
		WSAStartup(MAKEWORD(2, 2), &ws);//在win上需要自己动态加载lib
	}
}

int XTcp::CreateSocket() {
	sock = socket(AF_INET, SOCK_STREAM, 0);//socket可接收各种协议，这里采用TCP/IP协议,返回值是一个int
    //std::cout << sock << std::endl;
	if (sock == -1) {
		std::cout << "创建失败！" << std::endl;
	}
	return sock;
}

bool XTcp::Bind(unsigned short port) {
	//服务端信息初始化
	sockaddr_in saddr;
	saddr.sin_family = AF_INET;//确定协议
	saddr.sin_port = htons(port);//端口号，字节序进行转换
	saddr.sin_addr.s_addr = htonl(0);//ip地址，0表示任意ip都可以接收（外，主机自己）


	//绑定端口
	//int  winbind = bind(sock, (sockaddr*)&saddr, sizeof(saddr));
	if (::bind(sock, (sockaddr*)&saddr, sizeof(saddr)) != 0) {
		std::cout << "绑定端口失败！" << std::endl;
		return false;
	}
	std::cout << port << "绑定端口成功！" << std::endl;
	listen(sock, 10);
	return true;
}

XTcp XTcp::Accept() { //用户可以通过返回的tcp的socket来判断本次接收成功还是失败
	XTcp tcp;
	sockaddr_in caddr;
	int len = sizeof(caddr);
	int client = accept(sock, (sockaddr*)&caddr, &len);//返回一个socket用来与服务器进行独立通信,可以返回客户端的地址以及大小
	if (client <= 0) return tcp;
    tcp.ip = inet_ntoa(caddr.sin_addr);//获取ip地址
	tcp.port = ntohs(caddr.sin_port);//获取端口号
	tcp.sock = client;
	std::cout << "客户端 ip 是:" << tcp.ip.c_str() << " 客户端端口为:" << tcp.port << std::endl;
	std::cout << client << "进行了连接" << std::endl;
	return tcp;
}

void XTcp::Close() {
	if (sock <= 0) return;
	closesocket(sock);
}


int XTcp::Recv(char *buf, int bufsize) {
	
	return recv(sock, buf, bufsize, 0);
}
int XTcp::Send(const char *buf, int sendsize) {
	int s = 0;
	while(s!=sendsize){
		int len = send(sock, buf + s, sendsize - s, 0);
		if (len <= 0) break;
		s += len;
	}
	return s;
}