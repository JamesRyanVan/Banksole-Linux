#include "Accounts.h"

void Accounts::initialize() {
	string input;
	Console console = *new Console();
	console.clear(0);
	string db = getdir();
	if(file_exists(db)) {
		/*cout<<"Database found.\n";
		cout<<"Using " + db;
		cout<<"\n";
		console.clear(1000000);*/
	} else {
		cout<<"Database not found.\n";
		cout<<"This is where we were looking: " + db + "\n\n";
		cout<<"Would you like to enter the path manually? (Y/N)\n";
		while (true) {
			cin >> input;
			if(input == "Y" || input == "y" || input == "N" || input == "n")
				break;
			cout<<"Lets try that again. Would you like to enter the path manually, Y or N?\n";
		}
		if(input == "Y" || input == "y") {
			cout<<"Alright. Please enter your path. (Enter C to cancel)\n";
			while(true) {
				cin >> input;
				db = input;
				if(file_exists(db)) {
					cout<<"Database found.\n";
					cout<<"Using " + db;
					cout<<"\n";
					console.clear(1000000);
					input = "";
					break;
				}
				else if(input == "C") {
					break;
				}
				else {
					cout<<"Database not found.\n";
					cout<<"This is where we looked: " + db + "\n\n";
					cout<<"Please enter a different path:\n";
				}
			}
		}
		if(input == "N" || input == "n" || input == "c" || input == "C") {
			cout<<"Would you like us to (re)make the default database? (Y/N)\n";
			while (true) {
				cin >> input;
				if(input == "Y" || input == "y" || input == "N" || input == "n")
					break;
				cout<<"Lets try that again. Would you like us to (re)make the default database, Y or N?\n";
			}
			if(input == "Y" || input == "y") {
				if(build_db(db)) {
					cout<<"Database built Successfully\n";
					console.clear(2000000);
				}
			}
		}
	}
	import_db(db);
	database_path = db;
}

bool Accounts::build_db(string db_path) {
	Json::Value database;   
    Json::Value vec(Json::arrayValue);
    vec.append(Json::Value(1));
    vec.append(Json::Value(2));
    vec.append(Json::Value(3));
    database["accounts"]["23971"]["fname"] = "James";
    database["accounts"]["23971"]["lname"] = "Van";
    database["accounts"]["23971"]["pin"] = "81dc9bdb52d04dc20036dbd8313ed055";
    database["accounts"]["23971"]["balance"] = 100000;
    database["accounts"]["23971"]["userlevel"] = 0;
    database["accounts"]["12345"]["fname"] = "John";
    database["accounts"]["12345"]["lname"] = "Doe";
    database["accounts"]["12345"]["pin"] = "81dc9bdb52d04dc20036dbd8313ed055";
    database["accounts"]["12345"]["balance"] = 2000;
    database["accounts"]["12345"]["userlevel"] = 1;
    ofstream db_file;
  	db_file.open(db_path.c_str());
  	db_file << database;
  	db_file.close();
    return 1;
}

bool Accounts::write_db(string db_path) {
	ofstream db_file;
  	db_file.open(db_path.c_str());
  	db_file << database;
  	db_file.close();
  	return 1;
}

void Accounts::import_db(string db_path) {
    Json::Reader reader;
    ifstream open_db(db_path.c_str(), ifstream::binary);
    bool parsingSuccessful = reader.parse(open_db, database, false);
    if (!parsingSuccessful)
    {
        cout<<"Invalid database format.";
    }
}

string Accounts::getdir() {
	char buffer[255];
	char *answer = getcwd(buffer, sizeof(buffer));
	string s_cwd;
	if (answer)
	{
    	s_cwd = answer;
	}
	return s_cwd + "/accounts/Accounts.json";
}

bool Accounts::file_exists(string db_path) {
	if(access(db_path.c_str(),F_OK) != -1) {
		ifstream file;
  		file.exceptions(ifstream::failbit | ifstream::badbit);
  			try {
    			file.open(db_path.c_str());
  			}
  			catch (const ifstream::failure& e) {
    			cout << "Exception opening/reading file.\n";
    			file.close();
    			return false;
  			}
  			file.close();
  			return true;
		}
	else{
		return false;
	}
}

string Accounts::login() {
	string username;
	string password;
	cout<<"Welcome, Please Login\n";
	while(true) {	
		cout<<"Login ID: ";
		cin >> username;
		cout<<"Password: ";
		int ch;
		for (;;) {
	        ch = getch();
	        if(ch == 10 && password.length() > 0)
	              break;
	         char c = ch;
	         password += c;
	    }
	    if (verifyLogin(username, passToMD5(trim(password)))) {
	    	break;
	    }
	    else {
	    	cout<<"\nInvalid Password or Username\n";
	    	ch = 0;
	    	password = "";
	    }
	}
	return username;
}

string Accounts::passToMD5(string password) {
	unsigned char result[MD5_DIGEST_LENGTH];
	MD5((unsigned char*)password.c_str(), password.size(), result);
	ostringstream sout;
	sout<<hex<<std::setfill('0');
	for(long long c: result)
	{
	    sout<<setw(2)<<(long long)c;
	}
	return sout.str();
}

bool Accounts::verifyLogin(string username, string password) {
	string pass = database["accounts"][username]["pin"].asString();
	pass = trim(pass);
	cout<<pass;
	cout<<"\n";
	cout<<password;

	if (pass == password) {
			curUserID = username;
			curUserLevel = database["accounts"][username]["userlevel"].asString();
			curUserFname = database["accounts"][username]["fname"].asString();
			curUserLname = database["accounts"][username]["lname"].asString();
			curUserBalance = database["accounts"][username]["balance"].asString();
		return 1;
	}
	return 0;
}

string Accounts::getAccounts() {
	return "";
};

string Accounts::getUserID() {
	return curUserID;
};

string Accounts::getBalance(string accountNum) {
	return database["accounts"][accountNum]["balance"].asString();
};

string Accounts::getUserLevel(string accountNum) {
	return database["accounts"][accountNum]["userlevel"].asString();
};

string Accounts::getUserFname(string accountNum) {
	return database["accounts"][accountNum]["fname"].asString();
};

string Accounts::getUserLname(string accountNum) {
	return database["accounts"][accountNum]["lname"].asString();
}

bool Accounts::deposit(string accountNum, int amount) {
	database["accounts"][accountNum]["balance"] = database["accounts"][accountNum]["balance"].asInt() + amount;
	if(write_db(database_path))
		return 1;
	else
		return 0;
};

bool Accounts::withdraw(string accountNum, int amount) {
	if(database["accounts"][accountNum]["balance"].asInt() - amount < 0) {
		cout<<"You do not have enough funds to withdraw that amount. ";
		return 0;
	}
	else {
		database["accounts"][accountNum]["balance"] = database["accounts"][accountNum]["balance"].asInt() - amount;
	}
	if(write_db(database_path))
		return 1;
	else
		return 0;
};

bool Accounts::transferFunds(string accountNum, int amount, string accountNum2) {
	if(database["accounts"][accountNum]["balance"].asInt() - amount < 0) {
		cout<<"You do not have enough funds to send that amount. ";
		return 0;
	}
	else if(!database["accounts"].isMember(accountNum2)) {
		cout<<"Account does not exist. ";
		return 0;
	}
	else if(accountNum == accountNum2) {
		cout<<"You can't send money to yourself silly. ";
		return 0;
	}
	else {
		database["accounts"][accountNum]["balance"] = database["accounts"][accountNum]["balance"].asInt() - amount;
		database["accounts"][accountNum2]["balance"] = database["accounts"][accountNum2]["balance"].asInt() + amount;
	}
	if(write_db(database_path))
		return 1;
	else
		return 0;
};

string Accounts::createNewUser() {
	return "";
};

string Accounts::removeUser() {
	return "";
};

string Accounts::trim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(),
            not1(ptr_fun<int, int>(isspace))));
    return s;
}

int Accounts::getch() {
    struct termios oldtc, newtc;
    int ch;
    tcgetattr(STDIN_FILENO, &oldtc);
    newtc = oldtc;
    newtc.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newtc);
    ch=getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldtc);
    return ch;
}

