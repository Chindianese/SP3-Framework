#pragma once
#include <string>
class ClientSystem
{
private:
	SOCKET sock;
	std::string name;
public:
	ClientSystem();
	~ClientSystem();

	void Init();
	void Update();
	void Send(std::string s);
};
