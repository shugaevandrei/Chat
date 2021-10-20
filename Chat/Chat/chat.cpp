#pragma once
#include <iostream> 
#include <string> 
#include "user.h" 
#include "chat.h" 
#include "global.h" 
using std::string;

bool Chat::regUser(string name, string login, string password) {
	if (users.empty()) {
		users.push_back(User(name, login, password));
		std::cout << "����������, �� ������������������ ��� ������� " << users.back().getLogin() << std::endl;
		return true;
	}
	else {
		for (unsigned int i = 0; i < users.size(); ++i) {
			if (users.at(i).getLogin() == login) {
				std::cout << "������������ � ������� " << login << " ��� ����������" << std::endl;
				return false;
			}
		}
		users.push_back(User(name, login, password));
	}
	std::cout << "����������, �� ������������������ ��� ������� " << users.back().getLogin() << std::endl;
	return true;
}

bool Chat::userLogin(string login, string password) {
	for (unsigned int i = 0; i < users.size(); ++i) {
		if (users.at(i).getLogin() == login) {
			if (users.at(i).getPassword() == password) {
				curUser = &users.at(i);
				std::cout << "�� ����� � ��� ��� ������� " << curUser->getLogin() << std::endl;
				return true;
			}
			else {
				std::cout << "������ ������ � �������, ���������� �����" << std::endl;
				return false;
			}
		}
	}
	std::cout << "������������ � ����� ������ �� ����������, ���������� �����" << std::endl;
	return false;
}

bool Chat::userlogout() {
	if (users.empty()) {
		std::cout << "� ���� ��� �������������" << std::endl;
		return false;
	}
	if (curUser == nullptr) {
		std::cout << "������������� ����������� ���� ���!" << std::endl;
		return false;
	}
	else {
		std::cout << "������������ " << curUser->getLogin() << " ����� �� ����" << std::endl;
		curUser = nullptr;
		return true;
	}
}

bool Chat::getAllUsersChat() {
	if (users.empty()) {
		std::cout << "������ ������������� ����" << std::endl;
		return false;
	}
	else {
		std::cout << "������ �������������" << std::endl;
		for (unsigned int i = 0; i < users.size(); ++i) {
			std::cout << users.at(i).getLogin() << std::endl;
		}
		return true;
	}

}

bool Chat::delUser(string login) {
	if (users.empty()) {
		std::cout << " � ���� ������ ���" << std::endl;
		return false;
	}
	for (unsigned int i = 0; i < users.size(); ++i) {
		if (users.at(i).getLogin() == login) {
			users.erase(users.begin() + i);
			std::cout << "������������ � ������ " << login << " ������" << std::endl;
			return true;
		}
	}
	std::cout << " ������ ������������ �� ����������" << std::endl;
	return false;
}