#include<iostream>
#include<netinet/in.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include<errno.h>
#include<string.h>
#include<stdio.h>
#include <unistd.h>

using namespace std;

class ServerSocket {
	private:
		sockaddr_in m_serveraddr;
		sockaddr_in m_clientaddr;
		bool m_connected;
		int m_port;
		int m_sockfd;
		int m_clientsockfd;
		

	public:
		ServerSocket():m_sockfd(-1),m_clientsockfd(-1),m_connected(0){}
		~ServerSocket(){}
		bool isConnected(){ return m_connected;}
		void CreateSocket(string hostname, int port);
		void AcceptConnect(string hostname, int port);
		void Disconnect(){ close(m_sockfd);}
		int SendData();
		int ReceiveData();
};
		


