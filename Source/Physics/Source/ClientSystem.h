#pragma once
#include <string>
class ClientSystem
{
private:
	u_long somelong;
	WSADATA w;
	SOCKET sock;
	sockaddr_in addr; // the address structure for a TCP socket
	std::string name;
public:
	ClientSystem();
	~ClientSystem();

	void Init();
	void Update();
	void Send(std::string s);
};
