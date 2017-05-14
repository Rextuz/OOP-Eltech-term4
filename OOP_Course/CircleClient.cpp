#include "CircleClient.h"
#include <iostream>
using std::cout;
using std::endl;
#include <sstream>
using std::stringstream;
CircleClient::CircleClient(double new_x, double new_y, double new_r) :Circle(new_x,
	new_y, new_r)
{
	cout << "Created rounded customer ID =" << this->Client::id << endl;
}
CircleClient::~CircleClient()
{
	cout << "rounded Removed client with ID =" << this->Client::id << endl;
}
void CircleClient::recieveMessage(Server* server, string from, string message)
{
	if (!this->parseMessage(message))
	{
		cout << "\tClient " << this->Client::id << " console:" << endl;
		cout << message << endl << endl;
	}
}
bool CircleClient::parseMessage(string message)
{
	stringstream ss(message);
	string s;
	ss >> s;
	if (s == "draw")
	{
		cout << "\tClient " << this->Client::id << " console:" << endl;
		cout << "Server: > ";
		this->draw();
		cout << endl;
		return true;
	}
	if (s == "turn")
	{
		cout << "\tClient " << this->Client::id << " console:" << endl;
		cout << "Server: > ";
		double angle;
		ss >> angle;
		this->turn(angle);
		cout << endl;
		return true;
	}
	if (s == "move")
	{
		cout << "\tClient " << this->Client::id << " console:" << endl;
		cout << "Server: > ";
		double new_x, new_y;
		ss >> new_x >> new_y;
		this->move(new_x, new_y);
		cout << endl;
		return true;
	}
	return false;
}