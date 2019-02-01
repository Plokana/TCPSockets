#include "server.h"
#include<stdlib.h>

using namespace std;
void ServerSocket::CreateSocket(string hostname, int port){
	m_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(m_sockfd <0){ perror("Sockfd error :");}
        cout<<"sockfd : "<<m_sockfd<<"\n";
        m_serveraddr.sin_addr.s_addr  = inet_addr(hostname.c_str());
        m_serveraddr.sin_family = AF_INET;
        m_serveraddr.sin_port = htons(port);

        if(bind(m_sockfd, (sockaddr *)&m_serveraddr, sizeof(m_serveraddr))<0) { perror("Bind error:");}
        listen(m_sockfd, 5);

}
void ServerSocket::AcceptConnect(string hostname, int port){
	cout<<"ServerSocket::Connect\n";
	socklen_t len = sizeof(m_clientaddr);
	if((m_clientsockfd = accept(m_sockfd, (struct sockaddr *)&m_clientaddr, &len))<0){perror("Accept error: ");}
	else {
	cout<<"clientsockfd : "<<m_clientsockfd<<"\n";
	m_connected = true;}
}

int ServerSocket::SendData(){
	char buf[300]= {"I am SERVER, saying HI to U"};
	int nBytes=0;
	if(isConnected()){
		nBytes=send(m_clientsockfd, buf, sizeof(buf), 0);
		cout<<"bytes send : "<<nBytes<<"\n";
	}
	return nBytes;
}

int ServerSocket::ReceiveData(){
	char buf[300];
	int nBytes=0;
	if(isConnected()){
		nBytes=recv(m_clientsockfd, buf, sizeof(buf), 0);

		cout<<"bytes received : "<<nBytes<<" "<<buf<<"\n";
	}
	return nBytes;

}

int main(int argc, char *argv[]){
	ServerSocket s;
	s.CreateSocket(argv[1], atoi(argv[2]));
	while(1){
	s.AcceptConnect(argv[1], atoi(argv[2]));
	s.ReceiveData();
	s.SendData();
	}
	s.Disconnect();
}


