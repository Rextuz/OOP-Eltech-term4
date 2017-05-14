#pragma once
#include "server.h"
#include <string>
using std::string;
class Client
{
private:
	friend class Server;
	static int next_id;
	bool online;
	virtual void recieveMessage(Server* server, string from, string message);
	void recieveSysMessage(Server* server, string message);
protected:
	int id;
public:
	Client();
	~Client();
	void goOnline(Server* server);
	void goOffline(Server* server);
	void registerOnServer(Server* server, string username);
	void leaveServer(Server* server);
	void sendMessage(Server* server, string to, string message);
	void sendAll(Server* server, string message);
};