#pragma once
#include <iostream> 
#include <string> 
using std::string;

class User {
private:
	string _name;
	string _login;
	string _password;
	string _outMessage; //хранение исхоядщего сообщения
	string _inMessage; //хранение входящего сообщения
	User* inUser = nullptr;//хранение информации об отправителя
	void outMessage(string Message) { _outMessage = Message; }
	void inMessage(string Message) { _inMessage = Message; }
public:
	User(const string Uname, const string Ulog, const string Upas) :_name(Uname), _login(Ulog), _password(Upas) {};
	//User() = default;
	~User() {};
	const string getLogin() { return _login; }
	User* getinUser() { return inUser; }
	const string getName() { return _name; }
	const string getPassword() { return _password; }
	const string getMessage() { return _inMessage; }
	const string getMyOutMessage() { return _outMessage; }

	bool getMessageUser();//получить входящее сообщение от другого пользователя
	bool sendMessageUser(string login, string Message);//отправить сообщение пользователю
	bool sendMessageUser(string Message);//отправить сообщение всем пользователям чата
};