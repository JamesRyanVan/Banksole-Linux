# Banksole

Banksole is a commandline program which mimics a banking system. Writen in C++, it allows users to deposit, withdraw, transfer fake curreny. This was written for a school project and is not meant in any form to be a real banking system. It comes with two accounts, administrator, and regular users. 

Users Can:
  - Deposit Money
  - Withdraw Money
  - View Balance
  - Transfer Money
  - Logout

Administrators Can:
  - Deposit Money
  - Withdraw Money
  - View Balance
  - Transfer Money
  - Logout
  - View User(s)
  - Create User [In dev]
  - Delete User [In dev]
  - Transfer funds between two users [In dev]

Banksole also saves users information to a json database, and hashes passwords with an MD5 hash (Please, never store passwords this way in real applications). This database is populated by default with one administator, and one user. To login as either, use this information: 

Administrator
> userID = 23971 
> password = 1234

User
> userID = 12345 
> password = 1234

### Tech

Banksole uses a number of open source projects to work properly:

* [JsonCPP] - A C++ library for interacting with JSON.
* [OpenSSL] - A library used for creating MD5 hashs.

### Installation

This has only been tested on Ubuntu 14.04.5 LTS, but should work on most distributions of linux.

Download and extract the [latest pre-built release](https://github.com/JamesRyanVan).


#### Building for source
For production release:
```sh
$ g++ banksystem/BankSystem.cpp accounts/Accounts.cpp console/Console.cpp json.cpp main.cpp -o Banksole -Wall -std=c++11 -lcrypto -lssl
```

### Todos

 - Admin Create User
 - Admin Delete User
 - Admin Transfer funds

License
----

MIT

   [JsonCPP]: <https://github.com/open-source-parsers/jsoncpp>
   [OpenSSL]: <https://github.com/openssl/openssl>
