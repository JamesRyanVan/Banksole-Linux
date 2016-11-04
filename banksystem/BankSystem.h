#ifndef BankSystem_h
#define BankSystem_h

#include "../accounts/Accounts.h"
#include "../console/Console.h"

#include <string>
#include <iostream>
#include <limits>

using namespace std;

class BankSystem {
public:
	void startup();
private:
	void usermenu(string accountNum, Accounts users, Console console);
	void adminmenu(string accountNum, Accounts users, Console console);
};

#endif