//#ifdef WIN32         //宏定义，在预处理时候，如果是，则添加其中代码语句，否则删除
//#include<windows.h>
//#endif

#include<windows.h>
#include<iostream>
#include<thread>
#include"XTcp.h"
using namespace std;

class TcpThread {
     
public:
	void Main() {
		//接收用户发来的数据
		char  buf[1024] = { 0 };
		while (1) {
			int le = client.Recv( buf, sizeof(buf) - 1);
			if (le <= 0) break;
			buf[le] = '\0';
			if (strstr(buf, "q") != NULL) { //客户端退出，打印退出成功日志
				char re[] = "退出成功！！\n";
				client.Send( re, strlen(re) + 1);
				break;
			}

			client.Send("ok\n", 4);//服务器返回ok
			cout << buf << endl;
		}
		//多线程处理多个用户
		client.Close();//使用完毕之后要将其关闭
		delete this;//使用结束后对自己做清理工作
	}
	XTcp client;
};





int main(int argc, char *argv[]) {

	//WSADATA ws;
	//WSAStartup(MAKEWORD(2, 2), &ws);//在win上需要自己动态加载lib

	//int sock =  socket(AF_INET, SOCK_STREAM, 0);//socket可接收各种协议，这里采用TCP/IP协议,返回值是一个int
	////std::cout << sock << std::endl;
	//if (sock == -1) {
	//	cout << "创建失败！" << endl;
	//	return -1;
	//}
	//TCP是面向连接的，TCP提供可靠性，实现了丢失重传，流量控制和拥堵控制，全双工

    //服务端信息初始化
	unsigned short port = 8080;
	if (argc > 1) {
		port = atoi(argv[1]);
	}

	XTcp server;
	server.CreateSocket();
	server.Bind(port);
	for (;;) {
		XTcp client = server.Accept();
		//	//创建线程
		TcpThread *th = new TcpThread();
		th->client = client; //将上面接收到的client传进去
		thread sth(&TcpThread::Main,th);//使用类中这个方法做为这个线程的入口函数，这里要理解
		sth.detach();//释放主线程拥有子线程的资源
	}
	server.Close();
	//sockaddr_in saddr;
	//saddr.sin_family = AF_INET;//确定协议
	//saddr.sin_port = htons(port);//端口号，字节序进行转换
	//saddr.sin_addr.s_addr = htonl(0);//ip地址，0表示任意ip都可以接收（外，主机自己）


	////绑定端口
	////int  winbind = bind(sock, (sockaddr*)&saddr, sizeof(saddr));
	//if (::bind(sock, (sockaddr*)&saddr, sizeof(saddr))!=0){
	//	cout << "绑定端口失败！" << endl;
	//	return -2;
	//}
	//cout << port << "绑定端口成功！" << endl;

	////监听用户连接
	//listen(sock, 10);//套接字，缓冲区大小，在一定时间内最多多少个

	////接收用户的连接,多线程处理，多客户端，每来一个客户端都创建一个线程
	//for (;;) {
	//	sockaddr_in caddr;
	//	int len = sizeof(caddr);
	//	int client = accept(sock, (sockaddr*)&caddr, &len);//返回一个socket用来与服务器进行独立通信,可以返回客户端的地址以及大小
	//	if (client <= 0) break;
	//	char *ip = inet_ntoa(caddr.sin_addr);//获取ip地址
	//	unsigned short cport = ntohs(caddr.sin_port);//获取端口号
	//	cout << "客户端 ip 是:" << ip << " 客户端端口为:" << cport << endl;
	//	cout << client << "进行了连接" << endl;

	//	//创建线程
	//	TcpThread *th = new TcpThread();
	//	th->client = client; //将上面接收到的client传进去
	//	thread sth(&TcpThread::Main,th);//使用类中这个方法做为这个线程的入口函数，这里要理解
	//	sth.detach();//释放主线程拥有子线程的资源

	//}



/*
	//接收用户发来的数据
	char  buf[1024] = { 0 };
	while (1) {
	   int le = recv(client, buf,sizeof(buf)-1, 0);
	   if (le <= 0) break;
	   buf[le] = '\0';
	   if (strstr(buf, "q") != NULL) { //客户端退出，打印退出成功日志
		   char re[] = "退出成功！！\n";
		   send(client, re, strlen(re) + 1, 0);
		   break;
	   }

	   send(client, "ok\n", 4, 0);//服务器返回ok
	   cout << buf << endl;
	}
	//多线程处理多个用户
*/
	//closesocket(sock);//使用完毕之后要将其关闭
	//getchar();
	return 0;
}