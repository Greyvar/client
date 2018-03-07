#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>
#include <unistd.h>

#include "NetworkManager.hpp"

using namespace std;

void NetworkManager::connectToServer() {
	char* buffer[1024];

	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in server;
	short int port = 1337;

	memset(&server, 0, sizeof(server));

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(port);

	int connectResult = connect(sock, (struct sockaddr *) &server, sizeof(server));

	if (connectResult) {
		cout << "Connected" << endl;
	} else {
		cerr << "Connection failed" << errno << endl; 
//		close(sock);
		return;
	}

	recv(sock, buffer, sizeof(buffer), 0);

	cout << "recv: " << buffer << endl;
	close(sock);
}
