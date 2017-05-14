#include "server.h"
#include <iostream>
using std::cout;
using std::endl;
/************/
/* PRIVATE */
/* || */
/* \/ */
/************/
int Server::next_id = 0;
struct Server::User
{
public:
	User(Client* client, string username)
	{
		setlocale(LC_ALL, "Russian");
		this->client = client;
		this->username = username;
		this->online = true;
	}
	~User()
	{
		cout << "User" << username << "deleted" << endl;
	}
	Client* client;
	string username;
	bool online;
	vector<Message*> messages;
};
struct Server::Message
{
	string from;
	string message;
};
bool Server::nameIsFree(string username)
{
	for (unsigned int i = 0; i < registered_users.size(); i++)
	{
		if (registered_users[i]->username == username)
			return false;
	}
	return true;
}
void Server::setOnline(Client* client)
{
	User* user = findUserByClient(client);
	user->online = true;
	serverMessage("User" + user->username + "has logged");
	sendStored(user);
}
void Server::setOffline(Client* client)
{
	User* user = findUserByClient(client);
	user->online = false;
	serverMessage("User" + user->username + "left the network");
}
bool Server::registerUser(Client* client, string username)
{
	if (nameIsFree(username))
	{
		User* new_user = new User(client, username);
		registered_users.push_back(new_user);
		serverMessage("User" + new_user->username + "is registered");
		return true;
	}
	return false;
}
void Server::deleteUser(Client* client)
{
	for (unsigned int i = 0; i < registered_users.size(); i++)
	{
		if (registered_users[i]->client == client)
		{
			serverMessage("User" + registered_users[i]->username + "removed from server");
			delete registered_users[i];
			for (unsigned int j = i; j < registered_users.size(); j++)
			{
				if (j + 1 != registered_users.size())
				{
					registered_users[j] = registered_users[j + 1];
				}
			}
			registered_users.pop_back();
		}
	}
}
Server::User* Server::findUserByUsername(string username)
{
	for (unsigned int i = 0; i < registered_users.size(); i++)
	{
		if (registered_users[i]->username == username)
			return registered_users[i];
	}
	return nullptr;
}
Server::User* Server::findUserByClient(Client* client)
{
	for (unsigned int i = 0; i < registered_users.size(); i++)
	{
		if (registered_users[i]->client == client)
			return registered_users[i];
	}
	return nullptr;
}
void Server::sendMessage(Client* from, string to, string message)
{
	User* user = findUserByUsername(to);
	if (user == nullptr)
	{
		from->recieveMessage(this, to, "No user with that name");
		return;
	}
	Client* client = user->client;
	if (user->online)
	{
		client->recieveMessage(this, findUserByClient(from)->username, message);
		delivered(findUserByClient(from), findUserByUsername(to));
	}
	else
	{
		Message* MSG = new Message();
		MSG->from = findUserByClient(from)->username;
		MSG->message = message;
		user->messages.push_back(MSG);
		from->recieveSysMessage(this, "User not online");
		delivered(findUserByClient(from), findUserByUsername(to));
	}
}
void Server::sendStored(User* user)
{
	if (user->messages.empty())
		return;
	for (unsigned int i = 0; i < user->messages.size(); i++)
		user->client->recieveMessage(this, user->messages[i]->from, user->messages[i]->message);
	while (!user->messages.empty())
		user->messages.pop_back();
}
void Server::sendAll(User* from, string message)
{
	for (unsigned int i = 0; i < registered_users.size(); i++)
	{
		if (registered_users[i]->online)
			registered_users[i]->client->recieveMessage(this, from->username,
				message);
	}
}
void Server::serverMessage(string message)
{
	string smessage = "Server: >" + message;
	for (unsigned int i = 0; i < registered_users.size(); i++)
		registered_users[i]->client->recieveSysMessage(this, smessage);
}
void Server::delivered(User* from, User* to)
{
	string sys_msg = "Message to user" + to->username + "delivered";
	from->client->recieveSysMessage(this, sys_msg);
}
/************/
/* PUBLIC */
/* || */
/* \/ */
/************/
Server::Server()
{
	setlocale(LC_ALL, "Russian");
	this->id = this->next_id;
	this->next_id++;
	cout << "Server ID =" << this->id << "created" << endl;
}
Server::~Server()
{
	for (unsigned int i = 0; i < registered_users.size(); i++)
		delete registered_users[i];
	cout << "Server ID =" << this->id << "deleted" << endl << endl;
}