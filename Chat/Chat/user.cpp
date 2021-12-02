#include <iostream> 
#include <string> 
#include <vector> 
#include "user.h"
#include "global.h"
#include "chat.h" 
using std::string;

bool User::sendMessageUser(string login, string Message) {
	if (users.empty()) {
		std::cout << "¬ чате нет пользователей" << std::endl;
		return false;
	}
	for(std::vector<User>::iterator it = users.begin(); it != users.end(); ++it){
		if (it->getLogin() == login) {//проверка, есть ли чате такой пользователь	
			this->outMessage(Message); //у себ€ сохран€ем исход€щее сообщение	
			it->inMessage(Message);  //у пользовател€ которому отправили- вход€щее
			it->inUser = this;//сохран€ем информацию об отправителе, допустим потом можно будет по этой ссылке посмотреть профиль пользовател€			
			std::cout << this->getLogin() << ": сообщение \"" << it->_inMessage << "\" отправлено пользователю " << it->getLogin() << std::endl;
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
	for (std::vector<User>::iterator it = users.begin(); it != users.end(); ++it) {
		it->inMessage(Message);  //у пользовател€ которому отправили- вход€щее
		it->inUser = this;//сохран€ем информацию об отправителе, допустим потом можно будет по этой ссылке посмотреть профиль пользовател€	
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
