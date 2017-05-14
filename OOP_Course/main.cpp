#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <conio.h>
#include <Windows.h>
#include "server.h"
#include "CircleClient.h"
#include "PentagonClient.h"
void displayComment(string comment)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, BACKGROUND_BLUE | FOREGROUND_GREEN |		FOREGROUND_INTENSITY);
	cout << comment << endl;
	SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN |		FOREGROUND_BLUE);
}
void run()
{
	displayComment("Created server, client, and rounded pentagonal client");
	Server *s = new Server();
	CircleClient cc(0, 0, 10);
	double* x = new double[6];
	double* y = new double[6];
	x[0] = 0; y[0] = 0;
	x[1] = 10; y[1] = 10;
	x[2] = 10; y[2] = -10;
	x[3] = 0; y[3] = -10;
	x[4] = -10; y[4] = -10;
	x[5] = -10; y[5] = 10;
	PentagonClient pc(x, y);
	displayComment("Clients register to the server");
	cc.registerOnServer(s, "Max"); // Rounded customer Max
	pc.registerOnServer(s, "Alex"); // Pentagonal client Alex
	displayComment("Rounded pentagonal, the client sends the message \"Hello World\"");
	cc.sendMessage(s, "Alex", "Hello World!");
	displayComment("Pentagonal rounded client sends the message \"Hi\"");
	pc.sendMessage(s, "Max", "Hi!");
	displayComment("Rounded pentagonal client asks to move to the coordinates (10, 10)");
	cc.sendMessage(s, "Alex", "move 10 10");
	displayComment("Pentagonal rounded client asks to move to the coordinates (-10, -10)");
	pc.sendMessage(s, "Max", "move -10 -10");
	displayComment("the client asks a Rounded pentagonal to rotate 90 degrees Appendix 1 : program Listing (~1.5707963267) radians");
	cc.sendMessage(s, "Alex", "turn 1.5707963267");
	displayComment("Pentagonal client asks a rounded rotate -90 degrees (~- 1.5707963267) radians");
	pc.sendMessage(s, "Max", "turn -1.5707963267");
	displayComment("Rounded pentagonal client asks to draw");
	cc.sendMessage(s, "Alex", "draw");
	displayComment("Pentagonal rounded client asks to draw");
	pc.sendMessage(s, "Max", "draw");
	displayComment("one More round and pentagonal clients are created and registered on the server");
	CircleClient cc2(-5, -5, 5);
	PentagonClient pc2(y, x);
	cc2.registerOnServer(s, "Circle");
	pc2.registerOnServer(s, "Pentagon");
	displayComment("First round the client asks everyone to draw");
	cc.sendAll(s, "draw");
	displayComment("exit from the testing function. Destructors");
}
int main()
{
	setlocale(LC_ALL, "");
	run();
	_getch();
	return 0;
}