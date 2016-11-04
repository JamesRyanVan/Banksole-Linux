#include "BankSystem.h"

void BankSystem::startup() {
	Console console = *new Console();
	Accounts users = *new Accounts();
	
	users.initialize();
	usermenu(users.login(), users, console);

	return;
}

void BankSystem::usermenu(string accountNum, Accounts users, Console console) {
	string fname = users.getUserFname(accountNum);
	string lname = users.getUserLname(accountNum);
	string userlevel = users.getUserLevel(accountNum);
	cout<<users.getUserLname(accountNum);

    while(true) {
    	console.clear(0);
		cout<<"Welcome " + fname + " " + lname + "\n";
		cout<<"MAIN MENU";
	    cout<<"\n\n1. Deposit";
	    cout<<"\n\n2. Withdraw";
	    cout<<"\n\n3. Balance Inquiry";
	    cout<<"\n\n4. Transfer Funds";
	    cout<<"\n\n5. Logout\n\n";

	    if (userlevel == "0") {
	    	cout<<"ADMIN OPTIONS";
	    	cout<<"\n\n6. View Account";
	    	cout<<"\n7. Create Account";
	    	cout<<"\n8. Delete Account";
	    	cout<<"\n9. Tranfer funds (Between different accounts)\n\n";
	    }

	    int option = 0;
	    int amount;
	    cout<<"Enter your menu selection: ";
	    cin >> option;

    	switch(option) {
    		case 1: {
    			console.clear(0);
    			cout<<"Deposit";
    			cout<<"\n\nPlease Enter the amount you wish to deposit.\n";
    			cin>>amount;
    			if(users.deposit(accountNum, amount))
    				cout<<"Successfully Deposited";
    			else
    				cout<<"Deposit Failed :(";
    			cout<<"\n\nPress enter to continue...";
    			cin.ignore(256,'\n');
    			cin.get();
    			break;
            }
            case 2: {
    			console.clear(0);
    			cout<<"Withdraw";
    			cout<<"\n\nPlease Enter the amount you wish to withdraw. Currrent Balance: $" + users.getBalance(accountNum) + "\n";
    			cin>>amount;
    			if(users.withdraw(accountNum, amount))
    				cout<<"Successfully Withdrawed";
    			else
    				cout<<"Withdraw Failed :(";
    			cout<<"\n\nPress enter to continue...";
    			cin.ignore(256,'\n');
    			cin.get();
    			break;
            }
            case 3: {
    			console.clear(0);
    			cout<<"Balance Inquiry";
    			cout<<"\n\nYour current bank balance is: $";
    			cout<<users.getBalance(accountNum)+"\n";
    			cout<<"Press enter to continue...";
    			cin.ignore(256,'\n');
    			cin.get();
    			break;
            }
            case 4: {
    			console.clear(0);
    			cout<<"Transfer Funds";
    			cout<<"\n\nSend funds to another account. Please enter the other account number: \n";
    			string accountNum2;
    			cin>>accountNum2;
    			cout<<"\nPlease Enter the amount you wish send. Currrent Balance: $" + users.getBalance(accountNum) + "\n";
    			cin>>amount;
    			if(users.transferFunds(accountNum, amount, accountNum2))
    				cout<<"Sent Successfully.";
    			else
    				cout<<"Failed to send. ";
    			cout<<"\n\nPress enter to continue...";
    			cin.ignore(256,'\n');
    			cin.get();
    			break;
            }
            case 5: {
            	cout<<"Goodbye\n";
            	console.clear(1000000);
            	return;
            	break;
            }
            case 6: {
            	if (userlevel == "1") {
            		break;
            	}
            	console.clear(0);
    			cout<<"View Account";
    			cout<<"\n\nPlease enter the account number of the user (Enter 1 to retrieve data from all accounts)\n";
    			string accountNum2;
    			cin>>amount;
    			if (amount == 1) {
    				cout<<users.getAccounts();
    			}
    			else {
    				cout<<"Account Data:\n\n";
    				cout<<users.getUserFname(accountNum2)+"\n";
    				cout<<users.getUserLname(accountNum2)+"\n";
    				cout<<users.getBalance(accountNum2)+"\n";
    				cout<<users.getUserLevel(accountNum2)+"\n";
    			}
    			cout<<"Press enter to continue...";
    			cin.ignore(256,'\n');
    			cin.get();
    			break;
            }
            case 7: {
            	break;
            }
            case 8: {
            	break;
            }
            case 9: {
            	break;
            }
            default: {
            	break;           	
            }
    	}
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
}

void BankSystem::adminmenu(string accountNum, Accounts users, Console console) {

}