#pragma once
#include <iostream> 
#include <string> 
#include <utility>//<-----
using std::string;

class User {
private:
	std::pair<string, string> _dataUser;
	string _password;
	string _outMessage; //�������� ���������� ���������
	string _inMessage; //�������� ��������� ���������
	User* inUser = nullptr;//�������� ���������� �� �����������
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

	bool getMessageUser();//�������� �������� ��������� �� ������� ������������
	bool sendMessageUser(string login, string Message);//��������� ��������� ������������
	bool sendMessageUser(string Message);//��������� ��������� ���� ������������� ����
};