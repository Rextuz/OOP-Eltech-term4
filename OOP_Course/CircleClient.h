#pragma once
#include "circle.h"
#include "client.h"
class CircleClient :public Circle, public Client
{
private:
	void recieveMessage(Server* server, string from, string message);
	bool parseMessage(string message);
public:
	CircleClient(double new_x, double new_y, double new_r);
	~CircleClient();
};