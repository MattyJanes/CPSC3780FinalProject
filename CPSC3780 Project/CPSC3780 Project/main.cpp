#include "pch.h"
#include "SimpleHeader.h"
#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <ws2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

void main()
{
	string exampleAddress = "127.0.0.1";
	//Start Winsock and bind socket to ipv4 and port then loop
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int winsock0k = WSAStartup(version, &data);
	if (winsock0k != 0) {
		cerr << "Unable to start Winsock." << winsock0k;
		return;
	}

	SOCKET inSocket = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in serverClue;
	serverClue.sin_addr.S_un.S_addr = inet_addr(exampleAddress.c_str());
	serverClue.sin_family = AF_INET;
	serverClue.sin_port = htons(54000); //Converts from a little to big endian

	if (bind(inSocket, (sockaddr*)&serverClue, sizeof(serverClue)) == SOCKET_ERROR) {
		cerr << "Unable to bind socket." << WSAGetLastError() << endl;
		return;
	}

	sockaddr_in clientAddress;
	int clientLength = sizeof(clientAddress);
	ZeroMemory(&clientAddress, clientLength);

	char buffer[1024];

	//Wait for the message and then display both the message and client info
	while (true) {
		ZeroMemory(buffer, 1024);

		int bytesIn = recvfrom(inSocket, buffer, 1024, 0, (sockaddr*)&clientAddress, &clientLength);
		if (bytesIn == SOCKET_ERROR) {
			cerr << "Error receiving data from client." << WSAGetLastError() << endl;
			continue;
		}
		char clientIP[256];
		ZeroMemory(clientIP, 256);

		inet_ntop(AF_INET, &clientAddress.sin_addr, clientIP, 256);

		cout << "Message received from: " << clientIP << " : " << buffer << endl;
	}

	//Close the socket and shutdown winsock
	closesocket(inSocket);
	WSACleanup();
}