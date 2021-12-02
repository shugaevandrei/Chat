#include <iostream> 
#include <string> 
#include <vector> 
#include "user.h"
#include "global.h"
#include "chat.h" 
using std::string;

bool User::sendMessageUser(string login, string Message) {
	if (users.empty()) {
		std::cout << "� ���� ��� �������������" << std::endl;
		return false;
	}
	for(std::vector<User>::iterator it = users.begin(); it != users.end(); ++it){
		if (it->getLogin() == login) {//��������, ���� �� ���� ����� ������������	
			this->outMessage(Message); //� ���� ��������� ��������� ���������	
			it->inMessage(Message);  //� ������������ �������� ���������- ��������
			it->inUser = this;//��������� ���������� �� �����������, �������� ����� ����� ����� �� ���� ������ ���������� ������� ������������			
			std::cout << this->getLogin() << ": ��������� \"" << it->_inMessage << "\" ���������� ������������ " << it->getLogin() << std::endl;
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
	for (std::vector<User>::iterator it = users.begin(); it != users.end(); ++it) {
		it->inMessage(Message);  //� ������������ �������� ���������- ��������
		it->inUser = this;//��������� ���������� �� �����������, �������� ����� ����� ����� �� ���� ������ ���������� ������� ������������	
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
