#include <iostream> 
#include <vector> 
#include <string>

using std::string;

class User {
private:
	string _name;
	string _login;
	string _password;
	string _outMessage; //хранение исхоядщего сообщения
	string _inMessage; //хранение входящего сообщения
	User* inUser = NULL;//хранение информации об отправителя
	void outMessage(string Message) { _outMessage = Message; }
	void inMessage(string Message) { _inMessage = Message; }
public:
	User(const string Uname, const string Ulog, const string Upas) :_name(Uname), _login(Ulog), _password(Upas) {};
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

std::vector<User> users;  //Вектор всех зарегистрированных пользователей
User* curUser = NULL;//храним указатель на текущего пользователя

bool User::sendMessageUser(string login, string Message) {
	if (users.empty()) {
		std::cout << "В чате нет пользователей" << std::endl;
		return 0;
	}
	for (unsigned int i = 0; i < users.size(); ++i) {
		if (users.at(i).getLogin() == login) {//проверка, есть ли чате такой пользователь	
			this->outMessage(Message); //у себя сохраняем исходящее сообщение	
			users.at(i).inMessage(Message);  //у пользователя которому отправили- входящее
			users.at(i).inUser = this;//сохраняем информацию об отправителе, допустим потом можно будет по этой ссылке посмотреть профиль пользователя			
			std::cout << this->getLogin() << ": сообщение \"" << users.at(i)._inMessage << "\" отправлено пользователю " << users.at(i).getLogin() << std::endl;
			return 1;
		}
	}
	std::cout << "Пользователя с таким логином не существует" << std::endl;
	return 0;
}

bool User::sendMessageUser(string Message) {
	if (users.empty()) {
		std::cout << "В чате нет пользователей" << std::endl;
		return 0;
	}
	std::cout << "пользователь " << this->getLogin() << " отправил cообщение \"" << Message << "\" всем пользователям чата " << std::endl;
	this->outMessage(Message); //у себя сохраняем исходящее сообщение
	for (unsigned int i = 0; i < users.size(); ++i) {
		users.at(i).inMessage(Message);  //у пользователя которому отправили- входящее
		users.at(i).inUser = this;//сохраняем информацию об отправителе, допустим потом можно будет по этой ссылке посмотреть профиль пользователя	
	}
	return 1;
}
bool User::getMessageUser() {
	if (curUser->getLogin() == this->getLogin()) {
		if (this->getMessage()[0] == '\0') {
			std::cout << this->getLogin() << ": входящих сообщений нет" << std::endl;
			return 0;
		}
		std::cout << this->getLogin() << ": последнее сообщение: \"" << this->getMessage() << "\" было от пользователя: " << inUser->getLogin() << std::endl;
		return 1;
	}
	std::cout << this->getLogin() << ": прежде чем прочитать сообщение, вам необходимо войти в чат" << std::endl;
	return 0;
}


class Chat {
private:
	const string _name;
public:
	Chat(const string nameChat) :_name(nameChat) {
		std::cout << "Чат " << _name << " создан" << std::endl;
	}

	bool regUser(string name, string login, string password);
	bool userLogin(string login, string password);
	bool userlogout();
	bool delUser(string login);
	bool getAllUsersChat();
};

bool Chat::regUser(string name, string login, string password) {
	if (users.empty()) {
		users.push_back(User(name, login, password));
		std::cout << "Поздравляю, вы зарегестрировались под логином " << users.back().getLogin() << std::endl;
		return 1;
	}
	else {
		for (unsigned int i = 0; i < users.size(); ++i) {
			if (users.at(i).getLogin() == login) {
				std::cout << "Пользователь с логином " << login << " уже существует" << std::endl;
				return 0;
			}
		}
		users.push_back(User(name, login, password));
	}
	std::cout << "Поздравляю, вы зарегестрировались под логином " << users.back().getLogin() << std::endl;
	return 1;
}

bool Chat::userLogin(string login, string password) {
	for (unsigned int i = 0; i < users.size(); ++i) {
		if (users.at(i).getLogin() == login) {
			if (users.at(i).getPassword() == password) {
				curUser = &users.at(i);
				std::cout << "Вы вошли в чат под логином " << curUser->getLogin() << std::endl;
				return 1;
			}
			else {
				std::cout << "Пароль введен с ошибкой, попробуйте снова" << std::endl;
				return 0;
			}
		}
	}
	std::cout << "Пользователя с таким именем не существует, попробуйте снова" << std::endl;
	return 0;
}

bool Chat::userlogout() {
	if (users.empty()) {
		std::cout << "В чате нет пользователей" << std::endl;
		return 0;
	}
	if (curUser == NULL) {
		std::cout << "Пользователей выполнивших вход нет!" << std::endl;
		return 0;
	}
	if (curUser != NULL) {
		std::cout << "Пользователь " << curUser->getLogin() << " вышел из чата" << std::endl;
		curUser = NULL;
		return 1;
	}
}

bool Chat::getAllUsersChat() {
	if (users.empty()) {
		std::cout << "Список пользователей пуст" << std::endl;
		return 0;
	}
	else {
		std::cout << "Список пользователей" << std::endl;
		for (unsigned int i = 0; i < users.size(); ++i) {
			std::cout << users.at(i).getLogin() << std::endl;
		}
		return 1;
	}

}

bool Chat::delUser(string login) {
	if (users.empty()) {
		std::cout << " В чате никого нет" << std::endl;
		return 0;
	}
	for (unsigned int i = 0; i < users.size(); ++i) {
		if (users.at(i).getLogin() == login) {
			users.erase(users.begin() + i);
			std::cout << "Пользователь с именем " << login << " удален" << std::endl;
			return 1;
		}
	}
	std::cout << " Такого пользователя не существует" << std::endl;
	return 0;
}

char ch;
int maxUsers;
string name;
string login;
string pass;
string message;
int main()
{
	setlocale(LC_ALL, "Russian");

	std::cout << "Введите название для чата" << std::endl;
	getline(std::cin, name);
	Chat chat0(name);


	do {
		std::cout << "ВЫБЕРЕТЕ ДЕЙСТВИЕ: \n"
			" R- регистрация нового пользователя\n"
			" I- войти в чат\n"
			" O- выйти из чата\n"
			" E- выход из программы\n"
			" A- список пользователей\n"
			" S- сотправить сообщение пользователю\n"
			" G- получить сообщение от пользователя\n"
			" M- сотправить сообщение все пользователям\n"
			" T- ответить пользователю на вхоядщее сообщение\n"
			" D- удалить пользователя\n"
			<< std::endl;
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
			if (users.empty())std::cout << "Для входа в чат необходимо заргистрировать хотя бы одного пользователя" << std::endl;
			else if (curUser == NULL) {
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
			else {
				std::cout << "Вход выполнен пользователем: " << curUser->getLogin() << std::endl;
				std::cout << "Для входа по новым именем необходимо выйти из текущего профиля" << std::endl;
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
			if (curUser == NULL)std::cout << "Прежде чем отправить сообщение, войдите в чат" << std::endl;
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
			if (curUser == NULL)std::cout << "Прежде чем получить сообщение, войдите в чат" << std::endl;
			else curUser->getMessageUser();
		}
		break;
		case 'M':
		{
			if (curUser == NULL)std::cout << "Прежде чем отправить сообщение, войдите в чат" << std::endl;
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
			if (curUser == NULL)std::cout << "Прежде чем ответить на сообщение, войдите в чат" << std::endl;
			else {
				if (curUser->getMessageUser()) {
					std::cout << "введите текст сообщения: ";
					std::cin.clear();
					std::cin.sync();
					getline(std::cin, message);
					curUser->sendMessageUser(curUser->getinUser()->getLogin(), message);
				}
			}
		}
		case 'D':
		{
			if (users.empty()) {
				std::cout << " В чате никого нет" << std::endl;
			}
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
