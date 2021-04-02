#include "pch.h"
#include "SimpleHeader.h"
#include <iostream>
#include <ws2tcpip.h>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

void main(int argC, char* argv[])
{
	const string txtFileExt = ".txt";
	const string inArg(argv[1]);

	//Start Winsock
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int winsock0k = WSAStartup(version, &data);
	if (winsock0k != 0) {
		cerr << "Unable to start Winsock." << winsock0k;
		return;
	}

	//Create socket
	SOCKET outSocket = socket(AF_INET, SOCK_DGRAM, 0);

	//Write out to the socket
	if (inArg != "-f") {
		string hostAddress(argv[2]);
		string portNumber(argv[3]);

		//Create hint structure
		sockaddr_in server;
		server.sin_family = AF_INET;
		server.sin_port = htons(stoi(portNumber));

		inet_pton(AF_INET, hostAddress.c_str(), &server.sin_addr);

		string s(argv[1]);
		int sendOK = sendto(outSocket, s.c_str(), s.size() + 1, 0, (sockaddr*)&server, sizeof(server));

		if (sendOK == SOCKET_ERROR) {
			cerr << "Error: " << WSAGetLastError() << endl;
		}

		//Close socket
		closesocket(outSocket);
		//Close winsock
		WSACleanup();
	} else {
		if (argv[2]) {
			string inFile(argv[2]);
			string hostAddress(argv[3]);
			string portNumber(argv[4]);
			if (inFile.size() >= txtFileExt.size() && inFile.compare(inFile.size() - txtFileExt.size(), txtFileExt.size(), txtFileExt) == 0) {
				//Create hint structure
				sockaddr_in server;
				server.sin_family = AF_INET;
				server.sin_port = htons(stoi(portNumber));

				inet_pton(AF_INET, hostAddress.c_str(), &server.sin_addr);

				char cBuff;
				string fileContents;

				ifstream file{ inFile };
				file >> noskipws;
				while (file >> cBuff) fileContents += cBuff;
				file.close();

				int sendOK = sendto(outSocket, fileContents.c_str(), fileContents.size() + 1, 0, (sockaddr*)&server, sizeof(server));

				if (sendOK == SOCKET_ERROR) {
					cerr << "Error: " << WSAGetLastError() << endl;
				}

				//Close socket
				closesocket(outSocket);
				//Close winsock
				WSACleanup();
			}
			else {
				cerr << "Error: Invalid file type, please use a .txt file" << endl;
			}
		}
		else {
			cerr << "Error: Invalid filename or type." << endl;
		}
	}
}