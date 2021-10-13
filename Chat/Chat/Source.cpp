#include <iostream> 
#include <vector> 
#include <string>

using std::string;

class User {
private:
	const string* _name;
	const string* _login;
	const string* _password;

	string* _outMessage = NULL; //хранение исхоядщего сообщения
	string* _inMessage = NULL; //хранение входящего сообщения
	User* inUser = NULL;

	void outMessage(string* Message) {
		_outMessage = Message;
	}
	void inMessage(string* Message) {
		_inMessage = Message;
	}
public:
	User(const string* Uname, const string* Ulog, const string* Upas) : _name(Uname), _login(Ulog), _password(Upas) {}
	~User() {};
	const string* getLogin()const {
		return _login;
	}
	const string* getPassword()const {
		return _password;
	}
	const string* getMessage() {
		return _inMessage;
	}
	const string* getMyOutMessage() {
		return _outMessage;
	}
	bool getMessageUser();//получить входящее сообщение от другого пользователя
	bool sendMessageUser(User& user, string* Message);//отправить сообщение пользователю
	bool sendMessageUser(string* Message);//отправить сообщение всем пользователям чата
	friend bool operator==(const User& user1, const User& user2);
};

std::vector<User>* users = NULL;  //Вектор всех зарегистрированных пользователей
std::vector<User>* usersChat = NULL;  //Вектор вошедших в чат
/*
bool User::sendMessageUser(User& user, char* Message) {

	for (int i = 0; i < usersChat->size(); ++i) {
		if (usersChat->at(i).getLogin() == this->getLogin()) {//проверка, есть ли чате ли сам пользователь желающий отправить сообщение

			for (int i = 0; i < usersChat->size(); ++i) {

				if (usersChat->at(i).getLogin() == user.getLogin()) {
					std::cout <<std::endl;
					std::cout << this<< std::endl;

					this->outMessage(Message); //у себя сохраняем исходящее сообщение
					user.inMessage(Message);  //у пользователя которому отправили- входящее
					user.inUser = this;//сохраняем информацию об отправителе, допустим потом можно будет по этой ссылке посмотреть профиль пользователя
					std::cout << this->getLogin() << ": сообщение \"" << user._inMessage << "\" отправлено пользователю " << user.getLogin() << std::endl;
					return 1;
				}
			}
			std::cout << "Пользователя с таким логином не существует" << std::endl;
			return 0;
		}

	}
	std::cout << "Прежде чем отправить сообщение, вам необходимо войти в чат" << std::endl;
	return 0;
}
*/
bool User::sendMessageUser(User& user, string* Message) {

	for (unsigned int i = 0; i < usersChat->size(); ++i) {
		if (usersChat->at(i).getLogin() == this->getLogin()) {//проверка, есть ли чате ли сам пользователь желающий отправить сообщение	

			for (unsigned int i = 0; i < usersChat->size(); ++i) {

				if (usersChat->at(i).getLogin() == user.getLogin()) {
					this->outMessage(Message); //у себя сохраняем исходящее сообщение	
					user.inMessage(Message);  //у пользователя которому отправили- входящее
					user.inUser = this;//сохраняем информацию об отправителе, допустим потом можно будет по этой ссылке посмотреть профиль пользователя			
					std::cout << this->getLogin() << ": сообщение \"" << user._inMessage << "\" отправлено пользователю " << user.getLogin() << std::endl;
					return 1;
				}
			}
			std::cout << "Пользователя с таким логином не существует" << std::endl;
			return 0;
		}

	}
	std::cout << "Прежде чем отправить сообщение, вам необходимо войти в чат" << std::endl;
	return 0;
}

bool User::getMessageUser() {
	for (unsigned int i = 0; i < usersChat->size(); ++i) {
		if (usersChat->at(i).getLogin() == this->getLogin()) {//проверка, есть ли чате ли сам пользователь желающий прочитать сообщение	
			if (this->getMessage() == NULL) {

				//std::cout<<"адрес вызывабщего объекта " << this<< std::endl;
				//std::cout<<this->_inMessage << std::endl;


				std::cout << this->getLogin() << ": входящих сообщений нет" << std::endl;
				return 0;
			}
			std::cout << this->getLogin() << ": последнее сообщение: \"" << this->getMessage() << "\" было от пользователя " << inUser->getLogin() << std::endl;
			return 1;
		}
	}
	std::cout << this->getLogin() << ": прежде чем прочитать сообщение, вам необходимо войти в чат" << std::endl;
	return 0;
}
bool User::sendMessageUser(string* Message) {
	if (usersChat->empty()) {
		std::cout << "В чате нет пользователей" << std::endl;
		return 0;
	}
	for (unsigned int i = 0; i < usersChat->size(); ++i) {
		this->sendMessageUser(usersChat->at(i), Message);
	}
	std::cout << "польователь " << this->getLogin() << " отправил cообщение всем пользователям чата " << std::endl;
	return 1;
}

bool operator==(const User& user1, const User& user2) {
	return (user1.getLogin() == user2.getLogin());
}

class Chat {
private:
	const string* _name;
	int _maxUsers;
public:
	Chat(const string* nameChat, const int max) :_name(nameChat), _maxUsers(max) {
		users = new std::vector<User>;
		usersChat = new std::vector<User>;
		std::cout << "Чат " << *_name << " на " << _maxUsers << " пользователей создан" << std::endl;
	}

	bool regUser(User& Username);
	bool userLogin(User& Username);
	bool regUser(string* name, string* login, string* password);
	bool userLogin(string* login, string* password);
	//bool userlogout(User& Username);
	bool userlogout(string* login);
	bool delUser(User& Username);
	bool getAllUsersChat();
};


bool Chat::regUser(User& Username) {

	if (users->empty()) {
		users->push_back(Username);
		std::cout << "Поздравляю, вы зарегестрировались под логином " << Username.getLogin() << std::endl;
		return 1;
	}
	else {
		for (unsigned int i = 0; i < users->size(); ++i) {
			if (users->at(i).getLogin() == Username.getLogin()) {
				std::cout << "Пользователь с таким логином уже существует" << std::endl;
				return 0;
			}
		}
		users->push_back(Username);
	}
	std::cout << "Поздравляю, вы зарегестрировались под логином " << Username.getLogin() << std::endl;
	return 1;
}


bool Chat::regUser(string* name, string* login, string* password) {
	if (users->empty()) {
		//users->
		static const string name1 = "bob";
		static const string login1 = "bob";
		static const string pass1 = "111";
		static User user0(&name1, &login1, &pass1);

		users->push_back(user0);
		std::cout << "Поздравляю, вы зарегестрировались под логином 0" << *users->back().getLogin() << std::endl;
		std::cout << "Размер вектора: " << users->size() << std::endl;
		return 1;
	}
	else {
		for (unsigned int i = 0; i < users->size(); ++i) {
			//for(auto i = users->begin(); i < users->end();++i){
				//std::cout << users->at(i).getLogin() << std::endl;
			if (*users->at(i).getLogin() == *login)

				//if(strcmp(login, login))
				//if (users->at() >getLogin() == *login)
			{
				std::cout << "Пользователь с логином " << *login << " " << *users->at(i).getLogin() << " уже существует" << std::endl;


				return 0;
			}
		}
		users->push_back(User(name, login, password));
	}
	std::cout << "Поздравляю, вы зарегестрировались под логином 1" << *users->back().getLogin() << std::endl;
	return 1;
}


bool Chat::userLogin(User& Username) {
	for (unsigned int i = 0; i < usersChat->size(); ++i) {
		if (usersChat->at(i).getLogin() == Username.getLogin()) {
			std::cout << "Пользователь с логином " << Username.getLogin() << " уже выполнил вход" << std::endl;
			return 0;
		}
	}
	usersChat->push_back(Username);
	std::cout << "Вы вошли в чат под логином " << Username.getLogin() << std::endl;
	return 1;
}


bool Chat::userLogin(string* login, string* password) {
	for (unsigned int i = 0; i < usersChat->size(); ++i) {
		if (usersChat->at(i).getLogin() == login) {
			std::cout << "Пользователь с логином " << login << " уже выполнил вход" << std::endl;
			return 0;
		}
	}

	for (unsigned int i = 0; i < users->size(); ++i) {
		if ((users->at(i).getPassword() == password) && (users->at(i).getLogin() == login)) {
			usersChat->push_back(users->at(i));
			std::cout << "Вы вошли в чат под логином " << users->at(i).getLogin() << std::endl;
			return 1;
		}
	}
	std::cout << "Введенные данные ошибочны, попробуйте снова" << std::endl;
	return 0;
}

/*
bool Chat::userlogout(User& Username) {
	if (usersChat->empty()) {
		std::cout << "В чате нет пользователей" << std::endl;
		return 0;
	}
	for (int i = 0; i < usersChat->size(); ++i) {
		if (usersChat->at(i).getLogin() == Username.getLogin()) {
			usersChat->erase(usersChat->begin() + i);
			std::cout << "пользователь " << Username.getLogin() << " вышел из чата" << std::endl;
			return 1;
		}
	}
	std::cout << "Пользователя с именем " << Username.getLogin() << " не было в чате" << std::endl;
	return 0;
}
*/

bool Chat::userlogout(string* login) {
	if (usersChat->empty()) {
		std::cout << "В чате нет пользователей" << std::endl;
		return 0;
	}
	for (unsigned int i = 0; i < usersChat->size(); ++i) {
		if (usersChat->at(i).getLogin() == login) {
			usersChat->erase(usersChat->begin() + i);
			std::cout << "пользователь " << login << " вышел из чата" << std::endl;
			return 1;
		}
	}
	std::cout << "Пользователя с логином " << login << " не было в чате" << std::endl;
	return 0;
}

bool Chat::delUser(User& Username) {
	if (users->empty()) return 0;
	for (unsigned int i = 0; i < users->size(); ++i) {
		if (users->at(i).getLogin() == Username.getLogin()) {
			users->erase(users->begin() + i);
			std::cout << "Пользователь с именем " << Username.getLogin() << " удален" << std::endl;
			return 1;
		}
	}
	std::cout << " Такого пользователя не существует" << std::endl;
	return 0;
}
bool Chat::getAllUsersChat() {
	if (users->empty()) {
		std::cout << "В чате нет пользователей" << std::endl;
		return 0;
	}

	for (unsigned int i = 0; i < usersChat->size(); ++i) {
		std::cout << usersChat->at(i).getLogin() << std::endl;
	}
	return 1;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	const int sizeNameChat = 30;
	int maxUsers;
	const int sizeNameUser = 30, sizeLoginUser = 30, sizePassUser = 30;
	string nameChat;

	std::cout << "Введите название для чата" << std::endl;
	//std::cin.getline(nameChat, sizeNameChat);
	getline(std::cin, nameChat);
	std::cout << "Введите максимальное количество пользователей чата" << std::endl;
	std::cin >> maxUsers;
	Chat chat0(&nameChat, maxUsers);

	char ch;

	do {
		std::cout << "ВЫБЕРЕТЕ ДЕЙСТВИЕ: \n" << " R- регистрация нового пользователя\n I- войти в чат\n O- выйти из чата\n E- выход из программы\nA- список пользователей\n" << std::endl;
		std::cin.clear();
		std::cin.sync();
		std::cin >> ch;
		std::cin.ignore();
		switch (ch) {
		case 'R':
		{
			string name;
			string login;
			string pass;

			std::cout << "введите имя новго пользователя: ";
			std::cin.clear();
			std::cin.sync();
			//std::cin.getline(name, sizeLoginUser);
			getline(std::cin, name);

			std::cout << "введите логин новго пользователя: ";
			std::cin.clear();
			std::cin.sync();
			//std::cin.getline(login, sizeLoginUser);
			getline(std::cin, login);

			std::cout << "введите пароль новго пользователя: ";
			std::cin.clear();
			std::cin.sync();
			//std::cin.getline(pass, sizePassUser);
			getline(std::cin, pass);

			chat0.regUser(&name, &login, &pass);
			std::cout << std::endl;
		}

		break;
		case 'I':
		{
			string login;
			string pass;
			//std::cout << &name << name << std::endl;
			//std::cout << &login << login << std::endl;
			//std::cout << &pass << pass << std::endl;


			std::cout << "введите логин пользователя: ";
			std::cin.clear();
			std::cin.sync();
			//std::cin.getline(login, sizeLoginUser);
			getline(std::cin, login);

			std::cout << "введите пароль пользователя: ";
			std::cin.clear();
			std::cin.sync();
			//std::cin.getline(pass, sizePassUser);
			getline(std::cin, pass);

			chat0.userLogin(&login, &pass);
			std::cout << std::endl;
		}
		break;
		case 'O':
		{
			string login;
			//std::cout << &name << name << std::endl;
			//std::cout << &login << login << std::endl;
			//std::cout << &pass << pass << std::endl;

			std::cout << "введите логин пользователя: ";
			std::cin.clear();
			std::cin.sync();
			//std::cin.getline(login, sizeLoginUser);
			getline(std::cin, login);

			chat0.userlogout(&login);
			std::cout << std::endl;
		}
		break;
		case 'A':
		{
			//for (unsigned int i = 0; i < users->size(); ++i) {
			//for (auto i = users->begin(); i < users->end(); ++i){
			//	std::cout << "GHBDRN" << std::endl;
			//	std::cout << users->at(i).getLogin()<< std::endl;
				//std::cout <<  << std::endl;
			//}
			std::cout << users->size() << std::endl;
			for (unsigned int i = 0; i < users->size(); ++i) {
				std::cout << *users->at(i).getLogin() << std::endl;
			}
		}
		break;
		default:
			std::cout << "некорректный ввод! Повторите снова" << std::endl;
			break;
		}
	} while (ch != 'E');

	/*
	char name0[] = "Boba";
	char name1[] = "Biba";
	char name2[] = "Pupa";
	char name3[] = "Lupa";

	char fakeName[] = "buba";

	char login0[] = "Boba";
	char login1[] = "Biba";
	char login2[] = "Pupa";
	char login3[] = "Lupa";

	char fakeLogin[] = "buba";

	char pass0[] = "1212";
	char pass1[] = "1213";
	char pass2[] = "1214";
	char pass3[] = "1215";

	char fakePass[] = "1216";

	chat0.regUser(name0, login0, pass0);
	chat0.regUser(name0, login0, pass0);

	chat0.regUser(name1, login1, pass1);
	chat0.regUser(name2, login2, pass2);
	chat0.regUser(name3, login3, pass3);

	chat0.userLogin(login0, pass0);
	chat0.userLogin(login0, pass0);

	chat0.userLogin(fakeLogin, pass1);
	chat0.userLogin(login1, pass1);
	chat0.userLogin(login2, pass2);

	chat0.getAllUsersChat();


	chat0.userlogout(login0);
	chat0.userlogout(login0);

	chat0.userlogout(login1);
	chat0.userlogout(login2);

	chat0.userlogout(login0);
	chat0.userlogout(login1);
	chat0.userlogout(login2);

	chat0.userLogin(login0, pass0);
	chat0.userLogin(login1, pass1);
	chat0.userLogin(login2, pass2);

	char mess0[] = "ку-ку";
	char mess1[] = "привет";
	char mess2[] = "Привет всем!";

	usersChat->at(0).sendMessageUser(usersChat->at(1), mess0);
	std::cout << std::endl;
	usersChat->at(1).getMessageUser();
	usersChat->at(0).getMessageUser();

	usersChat->at(1).sendMessageUser(usersChat->at(0), mess1);
	usersChat->at(0).getMessageUser();

	chat0.userlogout(login1);
	chat0.userLogin(login1, pass1);
	chat0.getAllUsersChat();
*/

//usersChat->at(1).getMessageUser();
//usersChat->at(0).getMessageUser();
//chat0.userLogin(login1, pass1);
//usersChat->at(1).getMessageUser();

//usersChat->at(0).sendMessageUser(mess2);

//usersChat->at(0).getMessageUser();
//usersChat->at(1).getMessageUser();
//usersChat->at(2).getMessageUser();
//auto iter = usersChat->begin();
	//for(int i = 0; i < usersChat->size(); ++i){

	//usersChat->at(i).getMessageUser();

	//std::cout <<&usersChat->at(i) << std::endl;

//}


//std::cout <<&usersChat->at(0)<< std::endl;
//std::cout <<&user0<<std::endl;
//std::cout <<&user1<<std::endl;
//std::cout <<&user2<<std::endl;
//std::cout <<&user3<<std::endl;

//user1.getMessageUser();
//user2.getMessageUser();
//user3.getMessageUser();

//std::cout << usersChat->at(0).getMessage() << usersChat->at(0).getLogin() << std::endl;
//std::cout << usersChat->at(1).getMessage() << usersChat->at(1).getLogin() << std::endl;
//std::cout << usersChat->at(2).getMessage() << usersChat->at(2).getLogin() << std::endl;
//std::cout << usersChat->at(3).getMessage() << usersChat->at(3).getLogin() << std::endl;

//user0.getMessageUser();
//user1.getMessageUser();


//for(int i = 0; i < usersChat->size(); ++i){
//	    std::cout<<&usersChat->at(i)<<std::endl;}

	return 0;
}
