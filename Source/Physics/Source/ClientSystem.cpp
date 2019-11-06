#include <winsock2.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <process.h>
#include "ClientSystem.h"
#include "Locator.h"
#pragma comment(lib, "Ws2_32.lib")

ClientSystem::ClientSystem()
{
}

ClientSystem::~ClientSystem()
{
	WSACleanup();
}

void __cdecl ReadThread(void* param)
{
	while (true)
	{
		SOCKET* sock = (SOCKET*)param;
		// do your threaded stuffs here
		fd_set fset;
		FD_ZERO(&fset);
		FD_SET(*sock, &fset);

		timeval tval;
		tval.tv_sec = 0;
		tval.tv_usec = 10000;

		if (select(0, &fset, 0, 0, &tval) > 0)
		{
			//if (FD_ISSET(sock, &fset))
			{
				char buffer[255]; // buffer that is 255 characters big
				int length = recv(*sock, buffer, sizeof(buffer), 0);
				if (length == 0)
					continue;
				if (length == SOCKET_ERROR)
				{
					std::cout << "Server went offline" << std::endl;
					break;
				}
				//std::cout << buffer << std::endl;
				std::string message = buffer;
				DEFAULT_LOG(message);
			}
		}
	}

	return;
}
void ClientSystem::Init()
{
	// init
	name = "user";
	//Startup
	int error = WSAStartup(0x0202, &w);
	if (error) // Something bad happened
	{
		std::cout << "Could not start Winsock" << std::endl;
		return;
	}

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // Create socket

	addr.sin_family = AF_INET; // Address family Internet
	addr.sin_port = htons(23456); // Assign port 23456 to this socket
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // To local host

	ioctlsocket(sock, FIONBIO, &somelong);

	// do not check == SOCKET_ERROR here because Async mode will always return SOCKET_ERROR
	connect(sock, (sockaddr*)&addr, sizeof(addr));
	send(sock, name.c_str(), name.length() + 1, 0);

	_beginthread(ReadThread, 0, &sock);
}

void ClientSystem::Update()
{
}

void ClientSystem::Send(std::string s)
{
	send(sock, s.c_str(), (int)s.length() + 1, 0);
	DEFAULT_LOG("sent");
}