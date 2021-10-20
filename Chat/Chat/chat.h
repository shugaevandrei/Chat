#pragma once
#include <iostream> 
#include <string> 
using std::string;

class Chat {
private:
	const string _name;
public:
	Chat(const string nameChat) :_name(nameChat) {
		std::cout << "Чат " << _name << " создан" << std::endl;
	}

	bool regUser(string name, string login, string password);
	bool userLogin(string login, string password);
	bool userlogout();
	bool delUser(string login);
	bool getAllUsersChat();
};
