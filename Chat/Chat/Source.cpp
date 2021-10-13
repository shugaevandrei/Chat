#include <iostream> 
#include <vector> 
#include <string>

using std::string;

class User {
private:
	const string* _name;
	const string* _login;
	const string* _password;

	string* _outMessage = NULL; //�������� ���������� ���������
	string* _inMessage = NULL; //�������� ��������� ���������
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
	bool getMessageUser();//�������� �������� ��������� �� ������� ������������
	bool sendMessageUser(User& user, string* Message);//��������� ��������� ������������
	bool sendMessageUser(string* Message);//��������� ��������� ���� ������������� ����
	friend bool operator==(const User& user1, const User& user2);
};

std::vector<User>* users = NULL;  //������ ���� ������������������ �������������
std::vector<User>* usersChat = NULL;  //������ �������� � ���
/*
bool User::sendMessageUser(User& user, char* Message) {

	for (int i = 0; i < usersChat->size(); ++i) {
		if (usersChat->at(i).getLogin() == this->getLogin()) {//��������, ���� �� ���� �� ��� ������������ �������� ��������� ���������

			for (int i = 0; i < usersChat->size(); ++i) {

				if (usersChat->at(i).getLogin() == user.getLogin()) {
					std::cout <<std::endl;
					std::cout << this<< std::endl;

					this->outMessage(Message); //� ���� ��������� ��������� ���������
					user.inMessage(Message);  //� ������������ �������� ���������- ��������
					user.inUser = this;//��������� ���������� �� �����������, �������� ����� ����� ����� �� ���� ������ ���������� ������� ������������
					std::cout << this->getLogin() << ": ��������� \"" << user._inMessage << "\" ���������� ������������ " << user.getLogin() << std::endl;
					return 1;
				}
			}
			std::cout << "������������ � ����� ������� �� ����������" << std::endl;
			return 0;
		}

	}
	std::cout << "������ ��� ��������� ���������, ��� ���������� ����� � ���" << std::endl;
	return 0;
}
*/
bool User::sendMessageUser(User& user, string* Message) {

	for (unsigned int i = 0; i < usersChat->size(); ++i) {
		if (usersChat->at(i).getLogin() == this->getLogin()) {//��������, ���� �� ���� �� ��� ������������ �������� ��������� ���������	

			for (unsigned int i = 0; i < usersChat->size(); ++i) {

				if (usersChat->at(i).getLogin() == user.getLogin()) {
					this->outMessage(Message); //� ���� ��������� ��������� ���������	
					user.inMessage(Message);  //� ������������ �������� ���������- ��������
					user.inUser = this;//��������� ���������� �� �����������, �������� ����� ����� ����� �� ���� ������ ���������� ������� ������������			
					std::cout << this->getLogin() << ": ��������� \"" << user._inMessage << "\" ���������� ������������ " << user.getLogin() << std::endl;
					return 1;
				}
			}
			std::cout << "������������ � ����� ������� �� ����������" << std::endl;
			return 0;
		}

	}
	std::cout << "������ ��� ��������� ���������, ��� ���������� ����� � ���" << std::endl;
	return 0;
}

bool User::getMessageUser() {
	for (unsigned int i = 0; i < usersChat->size(); ++i) {
		if (usersChat->at(i).getLogin() == this->getLogin()) {//��������, ���� �� ���� �� ��� ������������ �������� ��������� ���������	
			if (this->getMessage() == NULL) {

				//std::cout<<"����� ����������� ������� " << this<< std::endl;
				//std::cout<<this->_inMessage << std::endl;


				std::cout << this->getLogin() << ": �������� ��������� ���" << std::endl;
				return 0;
			}
			std::cout << this->getLogin() << ": ��������� ���������: \"" << this->getMessage() << "\" ���� �� ������������ " << inUser->getLogin() << std::endl;
			return 1;
		}
	}
	std::cout << this->getLogin() << ": ������ ��� ��������� ���������, ��� ���������� ����� � ���" << std::endl;
	return 0;
}
bool User::sendMessageUser(string* Message) {
	if (usersChat->empty()) {
		std::cout << "� ���� ��� �������������" << std::endl;
		return 0;
	}
	for (unsigned int i = 0; i < usersChat->size(); ++i) {
		this->sendMessageUser(usersChat->at(i), Message);
	}
	std::cout << "����������� " << this->getLogin() << " �������� c�������� ���� ������������� ���� " << std::endl;
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
		std::cout << "��� " << *_name << " �� " << _maxUsers << " ������������� ������" << std::endl;
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
		std::cout << "����������, �� ������������������ ��� ������� " << Username.getLogin() << std::endl;
		return 1;
	}
	else {
		for (unsigned int i = 0; i < users->size(); ++i) {
			if (users->at(i).getLogin() == Username.getLogin()) {
				std::cout << "������������ � ����� ������� ��� ����������" << std::endl;
				return 0;
			}
		}
		users->push_back(Username);
	}
	std::cout << "����������, �� ������������������ ��� ������� " << Username.getLogin() << std::endl;
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
		std::cout << "����������, �� ������������������ ��� ������� 0" << *users->back().getLogin() << std::endl;
		std::cout << "������ �������: " << users->size() << std::endl;
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
				std::cout << "������������ � ������� " << *login << " " << *users->at(i).getLogin() << " ��� ����������" << std::endl;


				return 0;
			}
		}
		users->push_back(User(name, login, password));
	}
	std::cout << "����������, �� ������������������ ��� ������� 1" << *users->back().getLogin() << std::endl;
	return 1;
}


bool Chat::userLogin(User& Username) {
	for (unsigned int i = 0; i < usersChat->size(); ++i) {
		if (usersChat->at(i).getLogin() == Username.getLogin()) {
			std::cout << "������������ � ������� " << Username.getLogin() << " ��� �������� ����" << std::endl;
			return 0;
		}
	}
	usersChat->push_back(Username);
	std::cout << "�� ����� � ��� ��� ������� " << Username.getLogin() << std::endl;
	return 1;
}


bool Chat::userLogin(string* login, string* password) {
	for (unsigned int i = 0; i < usersChat->size(); ++i) {
		if (usersChat->at(i).getLogin() == login) {
			std::cout << "������������ � ������� " << login << " ��� �������� ����" << std::endl;
			return 0;
		}
	}

	for (unsigned int i = 0; i < users->size(); ++i) {
		if ((users->at(i).getPassword() == password) && (users->at(i).getLogin() == login)) {
			usersChat->push_back(users->at(i));
			std::cout << "�� ����� � ��� ��� ������� " << users->at(i).getLogin() << std::endl;
			return 1;
		}
	}
	std::cout << "��������� ������ ��������, ���������� �����" << std::endl;
	return 0;
}

/*
bool Chat::userlogout(User& Username) {
	if (usersChat->empty()) {
		std::cout << "� ���� ��� �������������" << std::endl;
		return 0;
	}
	for (int i = 0; i < usersChat->size(); ++i) {
		if (usersChat->at(i).getLogin() == Username.getLogin()) {
			usersChat->erase(usersChat->begin() + i);
			std::cout << "������������ " << Username.getLogin() << " ����� �� ����" << std::endl;
			return 1;
		}
	}
	std::cout << "������������ � ������ " << Username.getLogin() << " �� ���� � ����" << std::endl;
	return 0;
}
*/

bool Chat::userlogout(string* login) {
	if (usersChat->empty()) {
		std::cout << "� ���� ��� �������������" << std::endl;
		return 0;
	}
	for (unsigned int i = 0; i < usersChat->size(); ++i) {
		if (usersChat->at(i).getLogin() == login) {
			usersChat->erase(usersChat->begin() + i);
			std::cout << "������������ " << login << " ����� �� ����" << std::endl;
			return 1;
		}
	}
	std::cout << "������������ � ������� " << login << " �� ���� � ����" << std::endl;
	return 0;
}

bool Chat::delUser(User& Username) {
	if (users->empty()) return 0;
	for (unsigned int i = 0; i < users->size(); ++i) {
		if (users->at(i).getLogin() == Username.getLogin()) {
			users->erase(users->begin() + i);
			std::cout << "������������ � ������ " << Username.getLogin() << " ������" << std::endl;
			return 1;
		}
	}
	std::cout << " ������ ������������ �� ����������" << std::endl;
	return 0;
}
bool Chat::getAllUsersChat() {
	if (users->empty()) {
		std::cout << "� ���� ��� �������������" << std::endl;
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

	std::cout << "������� �������� ��� ����" << std::endl;
	//std::cin.getline(nameChat, sizeNameChat);
	getline(std::cin, nameChat);
	std::cout << "������� ������������ ���������� ������������� ����" << std::endl;
	std::cin >> maxUsers;
	Chat chat0(&nameChat, maxUsers);

	char ch;

	do {
		std::cout << "�������� ��������: \n" << " R- ����������� ������ ������������\n I- ����� � ���\n O- ����� �� ����\n E- ����� �� ���������\nA- ������ �������������\n" << std::endl;
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

			std::cout << "������� ��� ����� ������������: ";
			std::cin.clear();
			std::cin.sync();
			//std::cin.getline(name, sizeLoginUser);
			getline(std::cin, name);

			std::cout << "������� ����� ����� ������������: ";
			std::cin.clear();
			std::cin.sync();
			//std::cin.getline(login, sizeLoginUser);
			getline(std::cin, login);

			std::cout << "������� ������ ����� ������������: ";
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


			std::cout << "������� ����� ������������: ";
			std::cin.clear();
			std::cin.sync();
			//std::cin.getline(login, sizeLoginUser);
			getline(std::cin, login);

			std::cout << "������� ������ ������������: ";
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

			std::cout << "������� ����� ������������: ";
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
			std::cout << "������������ ����! ��������� �����" << std::endl;
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

	char mess0[] = "��-��";
	char mess1[] = "������";
	char mess2[] = "������ ����!";

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
