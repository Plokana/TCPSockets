#include "client.h"

using namespace std;
void ClientSocket::CreateSocket(string hostname, int port){
	m_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(m_sockfd <0){ perror("Sockfd error ");}
        cout<<"sockfd : "<<m_sockfd<<"\n";
        m_serveraddr.sin_addr.s_addr  = inet_addr(hostname.c_str());
        m_serveraddr.sin_family = AF_INET;
        m_serveraddr.sin_port = htons(port);
	cout<<"port : "<<port<<" htons(port): "<<htons(port)<<endl;

}
void ClientSocket::Connect(string hostname, int port){
	cout<<"ClientSocket::Connect\n";
	cout<<"Port : "<<port<<"htons(port): "<<htons(port);
	int success = connect(m_sockfd, (struct sockaddr *)&m_serveraddr, sizeof(m_serveraddr));
	if(success<0){perror("Connect error "); m_connected = false;}
	else 	m_connected = true;
}

int ClientSocket::SendData(char * data){
	char buf[300];
	strcpy(buf,data);
	int nBytes=0;
	if(isConnected()){
		nBytes=send(m_sockfd, buf, sizeof(buf), 0);
		cout<<"bytes send : "<<nBytes<<"\n";
	}
	return nBytes;
}

int ClientSocket::ReceiveData(){
	char buf[300];
	int nBytes=0;
	if(isConnected()){
		nBytes=recv(m_sockfd, buf, sizeof(buf), 0);

		cout<<"bytes received : "<<nBytes<<"  "<<buf<<" \n";
	}
	return nBytes;

}

int main(int argc, char *argv[]){
	ClientSocket s;
	s.CreateSocket(argv[1], atoi(argv[2]));
	s.Connect(argv[1], atoi(argv[2]));
	s.SendData(argv[3]);
	s.ReceiveData();
	s.Disconnect();
}


