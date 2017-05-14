#include "client.h"
#include <iostream>
using std::cout;
using std::endl;
/************/
/* PRIVATE */
/* || */
/* \/ */
/************/
int Client::next_id = 1;
void Client::recieveMessage(Server* server, string from, string message)
{
	cout << "\tClient " << this->id << " console:" << endl;
	cout << "Message form" << from << "(Server: " << server->id << ")" << endl;
	cout << " \"" << message << "\"" << endl << endl;
}
void Client::recieveSysMessage(Server* server, string message)
{
	cout << "\tClient " << this->id << " console:" << endl;
	cout << message << endl << endl;
}
/************/
/* PUBLIC */
/* || */
/* \/ */
/************/
Client::Client()
{
	setlocale(LC_ALL, "Russian");
	this->id = this->next_id;
	cout << "Client with ID =" << this->id << "created" << endl;
	this->next_id++;
	online = true;
}
Client::~Client()
{
	cout << "Client with ID =" << this->id << "deleted" << endl;
}
void Client::goOnline(Server* server)
{
	server->setOnline(this);
}
void Client::goOffline(Server* server)
{
	server->setOffline(this);
}
void Client::registerOnServer(Server* server, string username)
{
	if (!server->registerUser(this, username))
	{
		cout << "\tClient " << this->id << " console:" << endl;
		cout << "Name \"" << username << "\" already occupied" << endl;
	}
}
void Client::leaveServer(Server* server)
{
	this->goOnline(server);
	server->deleteUser(this);
	cout << "Customer ID =" << this->id << "has left the server ID =" << server->id <<
		endl << endl;
}
void Client::sendMessage(Server* server, string to, string message)
{
	if (server->findUserByClient(this) != nullptr)
		server->sendMessage(this, to, message);
	else
	{
		cout << "\tClient " << this->id << " console:" << endl;
		cout << "Error! You are not registered on the server ID = " << server->id <<
			endl << endl;
	}
}
void Client::sendAll(Server* server, string message)
{
	if (server->findUserByClient(this) != nullptr)
		server->sendAll(server->findUserByClient(this), message);
	else
		cout << "Error! You are not registered on the server ID = " << server->id <<
		endl << endl;
}