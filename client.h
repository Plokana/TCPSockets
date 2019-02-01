#include<iostream>
#include<netinet/in.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include<errno.h>
#include<string.h>
#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>


using namespace std;

class ClientSocket {
	private:
		sockaddr_in m_serveraddr;
		//sockaddr_in m_clientaddr;
		bool m_connected;
		int m_port;
		int m_sockfd;
	//	int m_clientsockfd;
	//	string hostname;
		

	public:
		ClientSocket():m_sockfd(-1),m_connected(false){}
		~ClientSocket(){}
		bool isConnected(){ return m_connected;}
		void CreateSocket(string hostname, int port);
		void Connect(string hostname, int port);
		void Disconnect(){ close(m_sockfd);}
		int SendData(char* data);
		int ReceiveData();
};
		


