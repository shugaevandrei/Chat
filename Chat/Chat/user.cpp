#include <iostream> 
#include <string> 
#include "user.h"
#include "global.h"
#include "chat.h" 
using std::string;

bool User::sendMessageUser(string login, string Message) {
	if (users.empty()) {
		std::cout << "� ���� ��� �������������" << std::endl;
		return false;
	}
	for (unsigned int i = 0; i < users.size(); ++i) {
		if (users.at(i).getLogin() == login) {//��������, ���� �� ���� ����� ������������	
			this->outMessage(Message); //� ���� ��������� ��������� ���������	
			users.at(i).inMessage(Message);  //� ������������ �������� ���������- ��������
			users.at(i).inUser = this;//��������� ���������� �� �����������, �������� ����� ����� ����� �� ���� ������ ���������� ������� ������������			
			std::cout << this->getLogin() << ": ��������� \"" << users.at(i)._inMessage << "\" ���������� ������������ " << users.at(i).getLogin() << std::endl;
			return true;
		}
	}
	std::cout << "������������ � ����� ������� �� ����������" << std::endl;
	return false;
}

bool User::sendMessageUser(string Message) {
	if (users.empty()) {
		std::cout << "� ���� ��� �������������" << std::endl;
		return false;
	}
	std::cout << "������������ " << this->getLogin() << " �������� c�������� \"" << Message << "\" ���� ������������� ���� " << std::endl;
	this->outMessage(Message); //� ���� ��������� ��������� ���������
	for (unsigned int i = 0; i < users.size(); ++i) {
		users.at(i).inMessage(Message);  //� ������������ �������� ���������- ��������
		users.at(i).inUser = this;//��������� ���������� �� �����������, �������� ����� ����� ����� �� ���� ������ ���������� ������� ������������	
	}
	return true;
}
bool User::getMessageUser() {
	if (curUser->getLogin() == this->getLogin()) {
		if (this->getMessage()[0] == '\0') {
			std::cout << this->getLogin() << ": �������� ��������� ���" << std::endl;
			return false;
		}
		std::cout << this->getLogin() << ": ��������� ���������: \"" << this->getMessage() << "\" ���� �� ������������: " << inUser->getLogin() << std::endl;
		return true;
	}
	std::cout << this->getLogin() << ": ������ ��� ��������� ���������, ��� ���������� ����� � ���" << std::endl;
	return false;
}
