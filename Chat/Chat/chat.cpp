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
		std::cout << "Поздравляю, вы зарегестрировались под логином " << users.back().getLogin() << std::endl;
		return true;
	}
	else {
		for (unsigned int i = 0; i < users.size(); ++i) {
			if (users.at(i).getLogin() == login) {
				std::cout << "Пользователь с логином " << login << " уже существует" << std::endl;
				return false;
			}
		}
		users.push_back(User(name, login, password));
	}
	std::cout << "Поздравляю, вы зарегестрировались под логином " << users.back().getLogin() << std::endl;
	return true;
}

bool Chat::userLogin(string login, string password) {
	for (unsigned int i = 0; i < users.size(); ++i) {
		if (users.at(i).getLogin() == login) {
			if (users.at(i).getPassword() == password) {
				curUser = &users.at(i);
				std::cout << "Вы вошли в чат под логином " << curUser->getLogin() << std::endl;
				return true;
			}
			else {
				std::cout << "Пароль введен с ошибкой, попробуйте снова" << std::endl;
				return false;
			}
		}
	}
	std::cout << "Пользователя с таким именем не существует, попробуйте снова" << std::endl;
	return false;
}

bool Chat::userlogout() {
	if (users.empty()) {
		std::cout << "В чате нет пользователей" << std::endl;
		return false;
	}
	if (curUser == nullptr) {
		std::cout << "Пользователей выполнивших вход нет!" << std::endl;
		return false;
	}
	else {
		std::cout << "Пользователь " << curUser->getLogin() << " вышел из чата" << std::endl;
		curUser = nullptr;
		return true;
	}
}

bool Chat::getAllUsersChat() {
	if (users.empty()) {
		std::cout << "Список пользователей пуст" << std::endl;
		return false;
	}
	else {
		std::cout << "Список пользователей" << std::endl;
		for (unsigned int i = 0; i < users.size(); ++i) {
			std::cout << users.at(i).getLogin() << std::endl;
		}
		return true;
	}

}

bool Chat::delUser(string login) {
	if (users.empty()) {
		std::cout << " В чате никого нет" << std::endl;
		return false;
	}
	for (unsigned int i = 0; i < users.size(); ++i) {
		if (users.at(i).getLogin() == login) {
			users.erase(users.begin() + i);
			std::cout << "Пользователь с именем " << login << " удален" << std::endl;
			return true;
		}
	}
	std::cout << " Такого пользователя не существует" << std::endl;
	return false;
}