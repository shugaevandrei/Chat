#include <iostream> 
#include <string> 
#include "user.h"
#include "global.h"
#include "chat.h" 
using std::string;

bool User::sendMessageUser(string login, string Message) {
	if (users.empty()) {
		std::cout << "¬ чате нет пользователей" << std::endl;
		return false;
	}
	for (unsigned int i = 0; i < users.size(); ++i) {
		if (users.at(i).getLogin() == login) {//проверка, есть ли чате такой пользователь	
			this->outMessage(Message); //у себ€ сохран€ем исход€щее сообщение	
			users.at(i).inMessage(Message);  //у пользовател€ которому отправили- вход€щее
			users.at(i).inUser = this;//сохран€ем информацию об отправителе, допустим потом можно будет по этой ссылке посмотреть профиль пользовател€			
			std::cout << this->getLogin() << ": сообщение \"" << users.at(i)._inMessage << "\" отправлено пользователю " << users.at(i).getLogin() << std::endl;
			return true;
		}
	}
	std::cout << "ѕользовател€ с таким логином не существует" << std::endl;
	return false;
}

bool User::sendMessageUser(string Message) {
	if (users.empty()) {
		std::cout << "¬ чате нет пользователей" << std::endl;
		return false;
	}
	std::cout << "пользователь " << this->getLogin() << " отправил cообщение \"" << Message << "\" всем пользовател€м чата " << std::endl;
	this->outMessage(Message); //у себ€ сохран€ем исход€щее сообщение
	for (unsigned int i = 0; i < users.size(); ++i) {
		users.at(i).inMessage(Message);  //у пользовател€ которому отправили- вход€щее
		users.at(i).inUser = this;//сохран€ем информацию об отправителе, допустим потом можно будет по этой ссылке посмотреть профиль пользовател€	
	}
	return true;
}
bool User::getMessageUser() {
	if (curUser->getLogin() == this->getLogin()) {
		if (this->getMessage()[0] == '\0') {
			std::cout << this->getLogin() << ": вход€щих сообщений нет" << std::endl;
			return false;
		}
		std::cout << this->getLogin() << ": последнее сообщение: \"" << this->getMessage() << "\" было от пользовател€: " << inUser->getLogin() << std::endl;
		return true;
	}
	std::cout << this->getLogin() << ": прежде чем прочитать сообщение, вам необходимо войти в чат" << std::endl;
	return false;
}
