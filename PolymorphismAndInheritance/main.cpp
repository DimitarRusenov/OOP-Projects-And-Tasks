#include <iostream>

#include "Administrator.h"
#include "System.h"
using namespace std;

int main()
{

	System a("Admin", 999);
	a.addUser("Admin", "FirstUser", 15);
	a.addModerator("Admin", "SecondUser", 9);
	a.addUser("Admin", "ThirdUser", 34);
	a.addPost("SecondUser", "[text]", "random text", System::getPostNumber());
	a.addPost("SecondUser", "[text]", "testing", System::getPostNumber());
	a.view_post(0);
	a.view_post(1);
	a.removePost("SecondUser", 0);
	a.info();
	return 0;
}