#ifndef Accounts_h
#define Accounts_h

#include "../console/Console.h"
#include "../json/json.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <termios.h>
#include <unistd.h>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <openssl/md5.h>
#include <iomanip>

using namespace std;

class Accounts {
public:
	void initialize();
	string login();
	string getUserID();
	string getAccounts();
	string getBalance(string accountNum);
	string getUserLevel(string accountNum);
	string getUserFname(string accountNum);
	string getUserLname(string accountNum);
	bool deposit(string accountNum, int amount);
	bool withdraw(string accountNum, int amount);
	bool transferFunds(string accountNum, int amount, string accountNum2);
	string createNewUser();
	string removeUser();
private:
	int getch();
	bool file_exists(string db_path);
	bool build_db(string db_path);
	bool write_db(string db_path);
	void import_db(string db_path);
	bool verifyLogin(string username, string password);
	string passToMD5(string password);
	string trim(string &s);
	string getdir();
	Json::Value database;
	string database_path;
	string curUserID;
	string curUserLevel;
	string curUserFname;
	string curUserLname;
	string curUserBalance;
};

#endif