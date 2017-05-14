#pragma once
#include "pentagon.h"
#include "client.h"
class PentagonClient :public Pentagon, public Client
{
private:
	void recieveMessage(Server* server, string from, string message);
	bool parseMessage(string message);
public:
	PentagonClient(double* new_x, double* new_y);
	~PentagonClient();
};