#pragma once
#include<string>
using namespace std;
//ʵ�ַ�װ��
class XTcp
{
public:
	int CreateSocket();
	bool Bind(unsigned short port);
	XTcp Accept();
	void Close();
	int Recv(char *buf,int bufsize);
	int Send(const char *buf,int sendsize);
	XTcp();
	//virtual ~XTcp();
	//sock��ʶ����port��ip
	int sock = 0;
	unsigned short port = 0;
	string ip;
};

