#include <iostream> 
#include <vector> 
#include <string>

using std::string;

class User {
private:
	string _name;
	string _login;
	string _password;
	string _outMessage; //�������� ���������� ���������
	string _inMessage; //�������� ��������� ���������
	User* inUser = NULL;//�������� ���������� �� �����������
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

	bool getMessageUser();//�������� �������� ��������� �� ������� ������������
	bool sendMessageUser(string login, string Message);//��������� ��������� ������������
	bool sendMessageUser(string Message);//��������� ��������� ���� ������������� ����
};

std::vector<User> users;  //������ ���� ������������������ �������������
User* curUser = NULL;//������ ��������� �� �������� ������������

bool User::sendMessageUser(string login, string Message) {
	if (users.empty()) {
		std::cout << "� ���� ��� �������������" << std::endl;
		return 0;
	}
	for (unsigned int i = 0; i < users.size(); ++i) {
		if (users.at(i).getLogin() == login) {//��������, ���� �� ���� ����� ������������	
			this->outMessage(Message); //� ���� ��������� ��������� ���������	
			users.at(i).inMessage(Message);  //� ������������ �������� ���������- ��������
			users.at(i).inUser = this;//��������� ���������� �� �����������, �������� ����� ����� ����� �� ���� ������ ���������� ������� ������������			
			std::cout << this->getLogin() << ": ��������� \"" << users.at(i)._inMessage << "\" ���������� ������������ " << users.at(i).getLogin() << std::endl;
			return 1;
		}
	}
	std::cout << "������������ � ����� ������� �� ����������" << std::endl;
	return 0;
}

bool User::sendMessageUser(string Message) {
	if (users.empty()) {
		std::cout << "� ���� ��� �������������" << std::endl;
		return 0;
	}
	std::cout << "������������ " << this->getLogin() << " �������� c�������� \"" << Message << "\" ���� ������������� ���� " << std::endl;
	this->outMessage(Message); //� ���� ��������� ��������� ���������
	for (unsigned int i = 0; i < users.size(); ++i) {
		users.at(i).inMessage(Message);  //� ������������ �������� ���������- ��������
		users.at(i).inUser = this;//��������� ���������� �� �����������, �������� ����� ����� ����� �� ���� ������ ���������� ������� ������������	
	}
	return 1;
}
bool User::getMessageUser() {
	if (curUser->getLogin() == this->getLogin()) {
		if (this->getMessage()[0] == '\0') {
			std::cout << this->getLogin() << ": �������� ��������� ���" << std::endl;
			return 0;
		}
		std::cout << this->getLogin() << ": ��������� ���������: \"" << this->getMessage() << "\" ���� �� ������������: " << inUser->getLogin() << std::endl;
		return 1;
	}
	std::cout << this->getLogin() << ": ������ ��� ��������� ���������, ��� ���������� ����� � ���" << std::endl;
	return 0;
}


class Chat {
private:
	const string _name;
public:
	Chat(const string nameChat) :_name(nameChat) {
		std::cout << "��� " << _name << " ������" << std::endl;
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
		std::cout << "����������, �� ������������������ ��� ������� " << users.back().getLogin() << std::endl;
		return 1;
	}
	else {
		for (unsigned int i = 0; i < users.size(); ++i) {
			if (users.at(i).getLogin() == login) {
				std::cout << "������������ � ������� " << login << " ��� ����������" << std::endl;
				return 0;
			}
		}
		users.push_back(User(name, login, password));
	}
	std::cout << "����������, �� ������������������ ��� ������� " << users.back().getLogin() << std::endl;
	return 1;
}

bool Chat::userLogin(string login, string password) {
	for (unsigned int i = 0; i < users.size(); ++i) {
		if (users.at(i).getLogin() == login) {
			if (users.at(i).getPassword() == password) {
				curUser = &users.at(i);
				std::cout << "�� ����� � ��� ��� ������� " << curUser->getLogin() << std::endl;
				return 1;
			}
			else {
				std::cout << "������ ������ � �������, ���������� �����" << std::endl;
				return 0;
			}
		}
	}
	std::cout << "������������ � ����� ������ �� ����������, ���������� �����" << std::endl;
	return 0;
}

bool Chat::userlogout() {
	if (users.empty()) {
		std::cout << "� ���� ��� �������������" << std::endl;
		return 0;
	}
	if (curUser == NULL) {
		std::cout << "������������� ����������� ���� ���!" << std::endl;
		return 0;
	}
	if (curUser != NULL) {
		std::cout << "������������ " << curUser->getLogin() << " ����� �� ����" << std::endl;
		curUser = NULL;
		return 1;
	}
}

bool Chat::getAllUsersChat() {
	if (users.empty()) {
		std::cout << "������ ������������� ����" << std::endl;
		return 0;
	}
	else {
		std::cout << "������ �������������" << std::endl;
		for (unsigned int i = 0; i < users.size(); ++i) {
			std::cout << users.at(i).getLogin() << std::endl;
		}
		return 1;
	}

}

bool Chat::delUser(string login) {
	if (users.empty()) {
		std::cout << " � ���� ������ ���" << std::endl;
		return 0;
	}
	for (unsigned int i = 0; i < users.size(); ++i) {
		if (users.at(i).getLogin() == login) {
			users.erase(users.begin() + i);
			std::cout << "������������ � ������ " << login << " ������" << std::endl;
			return 1;
		}
	}
	std::cout << " ������ ������������ �� ����������" << std::endl;
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

	std::cout << "������� �������� ��� ����" << std::endl;
	getline(std::cin, name);
	Chat chat0(name);


	do {
		std::cout << "�������� ��������: \n"
			" R- ����������� ������ ������������\n"
			" I- ����� � ���\n"
			" O- ����� �� ����\n"
			" E- ����� �� ���������\n"
			" A- ������ �������������\n"
			" S- ���������� ��������� ������������\n"
			" G- �������� ��������� �� ������������\n"
			" M- ���������� ��������� ��� �������������\n"
			" T- �������� ������������ �� �������� ���������\n"
			" D- ������� ������������\n"
			<< std::endl;
		std::cin.clear();
		std::cin.sync();
		std::cin >> ch;
		std::cin.ignore();
		switch (ch) {
		case 'R':
		{
			std::cout << "������� ��� ����� ������������: ";
			std::cin.clear();
			std::cin.sync();
			do {
				getline(std::cin, name);
			} while (name[0] == '\0');

			std::cout << "������� ����� ����� ������������: ";
			std::cin.clear();
			std::cin.sync();
			do {
				getline(std::cin, login);
			} while (login[0] == '\0');

			std::cout << "������� ������ (�� ����� 3-� ��������) ����� ������������: ";
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
			if (users.empty())std::cout << "��� ����� � ��� ���������� ��������������� ���� �� ������ ������������" << std::endl;
			else if (curUser == NULL) {
				std::cout << "������� ����� ������������: ";
				std::cin.clear();
				std::cin.sync();
				getline(std::cin, login);

				std::cout << "������� ������ ������������: ";
				std::cin.clear();
				std::cin.sync();
				getline(std::cin, pass);

				chat0.userLogin(login, pass);
			}
			else {
				std::cout << "���� �������� �������������: " << curUser->getLogin() << std::endl;
				std::cout << "��� ����� �� ����� ������ ���������� ����� �� �������� �������" << std::endl;
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
			if (curUser == NULL)std::cout << "������ ��� ��������� ���������, ������� � ���" << std::endl;
			else {
				std::cout << "������� ����� ����������: ";
				std::cin.clear();
				std::cin.sync();
				getline(std::cin, login);

				std::cout << "������� ����� ��������� ����������: ";
				std::cin.clear();
				std::cin.sync();
				getline(std::cin, message);
				curUser->sendMessageUser(login, message);
			}
		}
		break;
		case 'G':
		{
			if (curUser == NULL)std::cout << "������ ��� �������� ���������, ������� � ���" << std::endl;
			else curUser->getMessageUser();
		}
		break;
		case 'M':
		{
			if (curUser == NULL)std::cout << "������ ��� ��������� ���������, ������� � ���" << std::endl;
			else {
				std::cout << "������� ����� ��������� ����������: ";
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
			if (curUser == NULL)std::cout << "������ ��� �������� �� ���������, ������� � ���" << std::endl;
			else {
				if (curUser->getMessageUser()) {
					std::cout << "������� ����� ���������: ";
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
				std::cout << " � ���� ������ ���" << std::endl;
			}
			else {
				std::cout << "������� ����� ������������: ";
				std::cin.clear();
				std::cin.sync();
				getline(std::cin, login);
				chat0.delUser(login);
			}
		}
		break;
		default:
		{
			if (ch != 'E')std::cout << "������������ �������! ���������� �����!" << std::endl;
		}
		break;

		}
	} while (ch != 'E');
	std::cout << "��������� ��� � ��� ������� ���!";
	return 0;
}
