#include <iostream> 
#include "windows.h"
#include "user.h"
#include "chat.h"
#include "global.h"


int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	std::cout << "Введите название для чата" << std::endl;
	getline(std::cin, name);
	Chat chat0(name);
	users.reserve(16);

	do {
		std::cout << "ВЫБЕРЕТЕ ДЕЙСТВИЕ: \n"
			<< regUser
			<< exitProg;
		if (!users.empty()) {
			std::cout
				<< listUser
				<< delUser;
			if (curUser == nullptr)
				std::cout << inChat;
			if (curUser != nullptr) {
				std::cout << outChat
					<< sendMes
					<< sendMessAll;
				if ((curUser->getMyOutMessage()[0] != '\0') || (curUser->getMessage()[0] != '\0')) {
					std::cout << getMes
						<< ansMes;
				}

			}
		}

		std::cin.clear();
		std::cin.sync();
		std::cin >> ch;
		std::cin.ignore();
		switch (ch) {
		case 'R':
		{
			std::cout << "введите имя новго пользователя: ";
			std::cin.clear();
			std::cin.sync();
			do {
				getline(std::cin, name);
			} while (name[0] == '\0');

			std::cout << "введите логин новго пользователя: ";
			std::cin.clear();
			std::cin.sync();
			do {
				getline(std::cin, login);
			} while (login[0] == '\0');

			std::cout << "введите пароль (не менее 3-х символов) новго пользователя: ";
			std::cin.clear();
			std::cin.sync();
			getline(std::cin, pass);
			do {
				getline(std::cin, pass);
			} while (pass.size() < 3);

			chat0.regUser(name, login, pass);
		}
		break;
		case 'I':
		{
			if (users.empty()) {
				std::cout << "В чате нет пользователей" << std::endl;
			}
			else if (curUser != nullptr) {
				std::cout << "Вход в чат уже выполнен пользователем: " << curUser->getLogin() << std::endl;
			}
			else {
				std::cout << "введите логин пользователя: ";
				std::cin.clear();
				std::cin.sync();
				getline(std::cin, login);

				std::cout << "введите пароль пользователя: ";
				std::cin.clear();
				std::cin.sync();
				getline(std::cin, pass);

				chat0.userLogin(login, pass);
			}
		}
		break;
		case 'O':
		{
			chat0.userlogout();
			std::cout << std::endl;
		}
		break;
		case 'S':
		{
			if (users.empty()) {
				std::cout << "В чате нет пользователей" << std::endl;
			}
			else {
				std::cout << "введите логин получателя: ";
				std::cin.clear();
				std::cin.sync();
				getline(std::cin, login);

				std::cout << "введите текст сообщения получателя: ";
				std::cin.clear();
				std::cin.sync();
				getline(std::cin, message);
				curUser->sendMessageUser(login, message);
			}
		}
		break;
		case 'G':
		{
			if (curUser == nullptr) {
				std::cout << "Для получения сообщения необходимо войти в чат: " << std::endl;
			}
			else curUser->getMessageUser();
		}
		break;
		case 'M':
		{
			if (users.empty()) {
				std::cout << "В чате нет пользователей" << std::endl;
			}
			else {
				std::cout << "введите текст сообщения получателя: ";
				std::cin.clear();
				std::cin.sync();
				getline(std::cin, message);
				curUser->sendMessageUser(message);
			}
		}
		break;
		case 'A':
		{
			chat0.getAllUsersChat();
		}
		break;
		case 'T':
		{
			if (curUser == nullptr)std::cout << "для ответа на сообщение необходимо войти в чат" << std::endl;
			else {
				std::cout << "введите текст сообщения: ";
				std::cin.clear();
				std::cin.sync();
				getline(std::cin, message);
				curUser->sendMessageUser(curUser->getinUser()->getLogin(), message);
			}
		}
		break;
		case 'D':
		{
			if (users.empty())std::cout << "В чате нет пользователей" << std::endl;
			else {
				std::cout << "введите логин пользователя: ";
				std::cin.clear();
				std::cin.sync();
				getline(std::cin, login);
				chat0.delUser(login);
			}
		}
		break;
		default:
		{
			if (ch != 'E')std::cout << "Некорректная команда! Попробуйте снова!" << std::endl;
		}
		break;

		}
	} while (ch != 'E');
	std::cout << "Приходите еще в наш дружный чат!";
	return 0;
}