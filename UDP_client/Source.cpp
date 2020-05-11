#include <iostream>
#include <WS2tcpip.h>
#include <string>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

void main(int argc, char* argv[]) // we can pass in a command line option
{
	//start up winsock
	WSADATA data;
	WORD version = MAKEWORD(2,2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk !=0)
	{
		cout << "cant start winsock" << wsOk;
		return;
	}

	//create a hint structure for the server
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(54000);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
	
	
	//Socket creation
	SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);
	//write out to that socket
	string s;
	cout << "what would you like to send" << endl;
	getline(cin,s);
	int sendOk = sendto(out, s.c_str(), s.size() + 1,0,(sockaddr*)&server, sizeof(server));
	if (sendOk == SOCKET_ERROR) 
	{
		cout << "that didnt work" << WSAGetLastError() << endl;
	}
	//close the socket
	closesocket(out);
	//close down winsock
	WSACleanup();
}