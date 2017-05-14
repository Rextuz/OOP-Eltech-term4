#ifndef _TESTS_H_
#define _TESTS_H_

#include <Windows.h>

#include <string>
#define String std::string

#include <iostream>
using std::cout;
using std::endl;

static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

#define log(s); \
	SetConsoleTextAttribute(handle, BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY); \
	cout << "test[" << __FUNCTION__ << "]: " << s << endl; \
	SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN |	FOREGROUND_BLUE);

#define WIN {log("TEST PASSED"); cout << endl; return true;}
#define FAIL {log("TEST FAILED"); cout << endl; return false;}

bool create_server(Server *server = nullptr);
bool move_circle(Circle *circle = nullptr);
bool create_pentagon(Pentagon *pentagon = nullptr);
bool create_client(Client *client = nullptr);
bool create_pentagon_client(PentagonClient *pentagonClient = nullptr);
bool register_client(Server *server = nullptr, Client *client = nullptr);
bool register_client_twice(Server *server = nullptr, Client *client = nullptr);
bool send_messages(Server *server = nullptr, CircleClient *cclient = nullptr, PentagonClient *pclient = nullptr);

bool create_server(Server *server) {
	log("Creating a server");
	server = new Server();
	if (server != nullptr) {
		log("Server created");
		WIN
	}
	else {
		log("Server not created");
		FAIL
	}
}

bool move_circle(Circle *circle) {
	double start_x = 0, start_y = 0, delta_x = 1, delta_y = 1;
	log("Creating circle (" << start_x << ", " << start_y << ")");
	circle = new Circle(start_x, start_y, 1);
	log("Moving circle: (" << start_x << ", " << start_y << ") + (" << delta_x << ", " << delta_y << ")");
	circle->move(start_x + 1, start_y + 1);
	double * newXY = circle->getXY();
	if (newXY[0] == start_x + delta_x)
		if (newXY[1] == start_y + delta_y) {
			WIN
		}
	FAIL
}

bool create_pentagon(Pentagon *pentagon) {
	log("Creating a pentagon");
	double* x = new double[6];
	double* y = new double[6];
	x[0] = 0; y[0] = 0;
	x[1] = 10; y[1] = 10;
	x[2] = 10; y[2] = -10;
	x[3] = 0; y[3] = -10;
	x[4] = -10; y[4] = -10;
	x[5] = -10; y[5] = 10;
	pentagon = new Pentagon(x, y);
	if (pentagon != nullptr)
		WIN
		FAIL
}

bool create_client(Client *client) {
	log("Creating a client");
	client = new Client();
	if (client != nullptr)
		WIN
		FAIL
}

bool create_pentagon_client(PentagonClient *pentagonClient) {
	log("Creating a pentagon client");
	double* x = new double[6];
	double* y = new double[6];
	x[0] = 0; y[0] = 0;
	x[1] = 10; y[1] = 10;
	x[2] = 10; y[2] = -10;
	x[3] = 0; y[3] = -10;
	x[4] = -10; y[4] = -10;
	x[5] = -10; y[5] = 10;
	pentagonClient = new PentagonClient(x, y);
	if (pentagonClient != nullptr)
		WIN
		FAIL
}

bool register_client(Server *server, Client *client) {
	log("Registering client");
	server = new Server();
	client = new Client();
	if (client->registerOnServer(server, "Client"))
		WIN
		FAIL
}

bool register_client_twice(Server * server, Client * client)
{
	log("Registering client");
	server = new Server();
	client = new Client();
	client->registerOnServer(server, "Client");
	if (client->registerOnServer(server, "Client"))
		FAIL
		WIN
}

bool send_messages(Server *server, CircleClient *cclient, PentagonClient *pclient) {
	bool res;
	log("Sending a message");
	server = new Server();

	cclient = new CircleClient(0, 0, 1);
	cclient->registerOnServer(server, "Circle");

	double* x = new double[6];
	double* y = new double[6];
	x[0] = 0; y[0] = 0;
	x[1] = 10; y[1] = 10;
	x[2] = 10; y[2] = -10;
	x[3] = 0; y[3] = -10;
	x[4] = -10; y[4] = -10;
	x[5] = -10; y[5] = 10;
	pclient = new PentagonClient(x, y);
	pclient->registerOnServer(server, "Pentagon");

	pclient->sendMessage(server, "Circle", "move 10 10");

	if (cclient->getXY()[0] != 10) {
		if (cclient->getXY()[1] != 10)
			FAIL
	}

	pclient->sendMessage(server, "Circle", "move 3 3");

	if (cclient->getXY()[0] != 3) {
		if (cclient->getXY()[1] != 3)
			FAIL
	}

	WIN
}

#endif