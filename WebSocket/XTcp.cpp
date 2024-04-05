#include "XTcp.h"
#include<windows.h>
#include<iostream>
#include<thread>



XTcp::XTcp() {
	static bool first = true;
	if (first) {
		first = false;
		WSADATA ws;
		WSAStartup(MAKEWORD(2, 2), &ws);//��win����Ҫ�Լ���̬����lib
	}
}

int XTcp::CreateSocket() {
	sock = socket(AF_INET, SOCK_STREAM, 0);//socket�ɽ��ո���Э�飬�������TCP/IPЭ��,����ֵ��һ��int
    //std::cout << sock << std::endl;
	if (sock == -1) {
		std::cout << "����ʧ�ܣ�" << std::endl;
	}
	return sock;
}

bool XTcp::Bind(unsigned short port) {
	//�������Ϣ��ʼ��
	sockaddr_in saddr;
	saddr.sin_family = AF_INET;//ȷ��Э��
	saddr.sin_port = htons(port);//�˿ںţ��ֽ������ת��
	saddr.sin_addr.s_addr = htonl(0);//ip��ַ��0��ʾ����ip�����Խ��գ��⣬�����Լ���


	//�󶨶˿�
	//int  winbind = bind(sock, (sockaddr*)&saddr, sizeof(saddr));
	if (::bind(sock, (sockaddr*)&saddr, sizeof(saddr)) != 0) {
		std::cout << "�󶨶˿�ʧ�ܣ�" << std::endl;
		return false;
	}
	std::cout << port << "�󶨶˿ڳɹ���" << std::endl;
	listen(sock, 10);
	return true;
}

XTcp XTcp::Accept() { //�û�����ͨ�����ص�tcp��socket���жϱ��ν��ճɹ�����ʧ��
	XTcp tcp;
	sockaddr_in caddr;
	int len = sizeof(caddr);
	int client = accept(sock, (sockaddr*)&caddr, &len);//����һ��socket��������������ж���ͨ��,���Է��ؿͻ��˵ĵ�ַ�Լ���С
	if (client <= 0) return tcp;
    tcp.ip = inet_ntoa(caddr.sin_addr);//��ȡip��ַ
	tcp.port = ntohs(caddr.sin_port);//��ȡ�˿ں�
	tcp.sock = client;
	std::cout << "�ͻ��� ip ��:" << tcp.ip.c_str() << " �ͻ��˶˿�Ϊ:" << tcp.port << std::endl;
	std::cout << client << "����������" << std::endl;
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