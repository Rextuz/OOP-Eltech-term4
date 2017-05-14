#pragma once
#include "client.h"
#include <string>
using std::string;
#include <vector>
using std::vector;
class Server
{
private:
	friend class Client;
		int id;
	static int next_id;
	struct User;
	struct Message;
	vector<User*> registered_users;
	bool nameIsFree(string username);
	User* findUserByUsername(string username);
	User* findUserByClient(Client* client);
	void setOnline(Client* client);
	void setOffline(Client* client);
	bool registerUser(Client* client, string username);
	void deleteUser(Client* client);
	void sendMessage(Client* from, string to, string message);
	void sendAll(User* from, string message);
	void sendStored(User* user);
	void serverMessage(string message);
	void delivered(User* from, User* to);
public:
	Server();
	~Server();
};