#pragma once
#include <iostream> 
#include <string> 
#include <utility>//<-----
using std::string;

class User {
private:
	std::pair<string, string> _dataUser;
	string _password;
	string _outMessage; //хранение исхоядщего сообщения
	string _inMessage; //хранение входящего сообщения
	User* inUser = nullptr;//хранение информации об отправителя
	void outMessage(string Message) { _outMessage = Message; }
	void inMessage(string Message) { _inMessage = Message; }
public:
	User(const string Uname, const string Ulog, const string Upas) : _password(Upas) {//<---
		_dataUser = make_pair(Ulog, Uname);//<----
	};
	~User() {};
	const string getLogin() { return _dataUser.first; }
	User* getinUser() { return inUser; }
	const string getName() { return  _dataUser.second;}
	const string getPassword() { return _password; }
	const string getMessage() { return _inMessage; }
	const string getMyOutMessage() { return _outMessage; }

	bool getMessageUser();//получить входящее сообщение от другого пользователя
	bool sendMessageUser(string login, string Message);//отправить сообщение пользователю
	bool sendMessageUser(string Message);//отправить сообщение всем пользователям чата
};