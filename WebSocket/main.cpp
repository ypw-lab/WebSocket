//#ifdef WIN32         //�궨�壬��Ԥ����ʱ������ǣ���������д�����䣬����ɾ��
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
		//�����û�����������
		char  buf[1024] = { 0 };
		while (1) {
			int le = client.Recv( buf, sizeof(buf) - 1);
			if (le <= 0) break;
			buf[le] = '\0';
			if (strstr(buf, "q") != NULL) { //�ͻ����˳�����ӡ�˳��ɹ���־
				char re[] = "�˳��ɹ�����\n";
				client.Send( re, strlen(re) + 1);
				break;
			}

			client.Send("ok\n", 4);//����������ok
			cout << buf << endl;
		}
		//���̴߳������û�
		client.Close();//ʹ�����֮��Ҫ����ر�
		delete this;//ʹ�ý�������Լ���������
	}
	XTcp client;
};





int main(int argc, char *argv[]) {

	//WSADATA ws;
	//WSAStartup(MAKEWORD(2, 2), &ws);//��win����Ҫ�Լ���̬����lib

	//int sock =  socket(AF_INET, SOCK_STREAM, 0);//socket�ɽ��ո���Э�飬�������TCP/IPЭ��,����ֵ��һ��int
	////std::cout << sock << std::endl;
	//if (sock == -1) {
	//	cout << "����ʧ�ܣ�" << endl;
	//	return -1;
	//}
	//TCP���������ӵģ�TCP�ṩ�ɿ��ԣ�ʵ���˶�ʧ�ش����������ƺ�ӵ�¿��ƣ�ȫ˫��

    //�������Ϣ��ʼ��
	unsigned short port = 8080;
	if (argc > 1) {
		port = atoi(argv[1]);
	}

	XTcp server;
	server.CreateSocket();
	server.Bind(port);
	for (;;) {
		XTcp client = server.Accept();
		//	//�����߳�
		TcpThread *th = new TcpThread();
		th->client = client; //��������յ���client����ȥ
		thread sth(&TcpThread::Main,th);//ʹ���������������Ϊ����̵߳���ں���������Ҫ���
		sth.detach();//�ͷ����߳�ӵ�����̵߳���Դ
	}
	server.Close();
	//sockaddr_in saddr;
	//saddr.sin_family = AF_INET;//ȷ��Э��
	//saddr.sin_port = htons(port);//�˿ںţ��ֽ������ת��
	//saddr.sin_addr.s_addr = htonl(0);//ip��ַ��0��ʾ����ip�����Խ��գ��⣬�����Լ���


	////�󶨶˿�
	////int  winbind = bind(sock, (sockaddr*)&saddr, sizeof(saddr));
	//if (::bind(sock, (sockaddr*)&saddr, sizeof(saddr))!=0){
	//	cout << "�󶨶˿�ʧ�ܣ�" << endl;
	//	return -2;
	//}
	//cout << port << "�󶨶˿ڳɹ���" << endl;

	////�����û�����
	//listen(sock, 10);//�׽��֣���������С����һ��ʱ���������ٸ�

	////�����û�������,���̴߳�����ͻ��ˣ�ÿ��һ���ͻ��˶�����һ���߳�
	//for (;;) {
	//	sockaddr_in caddr;
	//	int len = sizeof(caddr);
	//	int client = accept(sock, (sockaddr*)&caddr, &len);//����һ��socket��������������ж���ͨ��,���Է��ؿͻ��˵ĵ�ַ�Լ���С
	//	if (client <= 0) break;
	//	char *ip = inet_ntoa(caddr.sin_addr);//��ȡip��ַ
	//	unsigned short cport = ntohs(caddr.sin_port);//��ȡ�˿ں�
	//	cout << "�ͻ��� ip ��:" << ip << " �ͻ��˶˿�Ϊ:" << cport << endl;
	//	cout << client << "����������" << endl;

	//	//�����߳�
	//	TcpThread *th = new TcpThread();
	//	th->client = client; //��������յ���client����ȥ
	//	thread sth(&TcpThread::Main,th);//ʹ���������������Ϊ����̵߳���ں���������Ҫ���
	//	sth.detach();//�ͷ����߳�ӵ�����̵߳���Դ

	//}



/*
	//�����û�����������
	char  buf[1024] = { 0 };
	while (1) {
	   int le = recv(client, buf,sizeof(buf)-1, 0);
	   if (le <= 0) break;
	   buf[le] = '\0';
	   if (strstr(buf, "q") != NULL) { //�ͻ����˳�����ӡ�˳��ɹ���־
		   char re[] = "�˳��ɹ�����\n";
		   send(client, re, strlen(re) + 1, 0);
		   break;
	   }

	   send(client, "ok\n", 4, 0);//����������ok
	   cout << buf << endl;
	}
	//���̴߳������û�
*/
	//closesocket(sock);//ʹ�����֮��Ҫ����ر�
	//getchar();
	return 0;
}