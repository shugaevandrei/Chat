#include <iostream> 
#include <vector> 

class User{
private:
	const char *_name;
	const char *_login;
	const char *_password;
	
	char *_outMessage = NULL; //�������� ���������� ���������
	char *_inMessage = NULL; //�������� ��������� ���������
	User *inUser = NULL;
	
    void outMessage(char *Message){
    	_outMessage = Message;
	}
	void inMessage(char *Message){
    	_inMessage = Message;
	}
public:
	User(const char* Uname, const char* Ulog, const char* Upas): _name(Uname) ,_login(Ulog), _password(Upas){}
	~User(){};
	const char *getLogin()const{
		return _login;
	}
	const char *getPassword()const{
		return _password;
	}
	const char *getMessage(){
		return _inMessage;
	}
	const char *getMyOutMessage(){
		return _outMessage;
	}
	bool getMessageUser();//�������� �������� ��������� �� ������� ������������
	bool sendMessageUser(User& user, char *Message);//��������� ��������� ������������
	bool sendMessageUser(char *Message);//��������� ��������� ���� ������������� ����
	friend bool operator==(const User &user1, const User &user2);
};

std::vector<User> *users = NULL;  //������ ���� ������������������ �������������
std::vector<User> *usersChat= NULL;  //������ �������� � ���

bool User::sendMessageUser(User &user, char *Message){
	
	for(int i = 0; i < usersChat->size(); ++i){
		if(usersChat->at(i).getLogin() == this->getLogin()) {//��������, ���� �� ���� �� ��� ������������ �������� ��������� ���������	
			for(int i = 0; i < usersChat->size(); ++i){	
				if(usersChat->at(i).getLogin() == user.getLogin()){
					this->outMessage(Message); //� ���� ��������� ��������� ���������
					user.inMessage(Message);  //� ������������ �������� ���������- ��������
					user.inUser = this;//��������� ���������� �� �����������, �������� ����� ����� ����� �� ���� ������ ���������� ������� ������������			
					std::cout <<this->getLogin() << ": ��������� \""<<user._inMessage <<"\" ���������� ������������ "<<user.getLogin()<< std::endl;
					return 1;
				}
			}
			std::cout << "������������ � ����� ������� �� ����������"<< std::endl;
			return 0;		
		}
		
	}
	std::cout << "������ ��� ��������� ���������, ��� ���������� ����� � ���"<< std::endl;
	return 0;			
}
bool User::getMessageUser(){
	if(this->getMessage() == NULL){
		std::cout << "�������� ��������� ���" << std::endl;
		return 0;}
	
	for(int i = 0; i < usersChat->size(); ++i){
		if(usersChat->at(i).getLogin() == this->getLogin()){//��������, ���� �� ���� �� ��� ������������ �������� ��������� ���������		
			std::cout<<this->getLogin() <<": ��������� ���������: \""<<this->getMessage() <<"\" ���� �� ������������ " <<inUser->getLogin()<<std::endl;
			return 1;	
		}
	}
	std::cout <<this->getLogin()<< ": ������ ��� ��������� ���������, ��� ���������� ����� � ���"<< std::endl;
	return 0;
}
bool User::sendMessageUser(char *Message){
	if(usersChat->empty()){
		std::cout << "� ���� ��� �������������"<< std::endl;
		return 0;
	}
	//user.inMessage(Message);  //� ������������ �������� ���������- ��������
	//user.inUser = this;//��������� ���������� �� �����������, �������� ����� ����� ����� �� ���� ������ ���������� ������� ������������	
	//for(int i = 0; i < usersChat->size(); ++i){
		this->sendMessageUser(usersChat->at(0),Message);
		//this->sendMessageUser(usersChat->at(1),Message);
		//this->sendMessageUser(usersChat->at(2),Message);
		//this->sendMessageUser(usersChat->at(3),Message);
		
		std::cout<<usersChat->at(0).getMessage() << usersChat->at(0).getLogin()<<std::endl;
		std::cout<<usersChat->at(1).getMessage() << usersChat->at(1).getLogin()<< std::endl;
		std::cout<<usersChat->at(2).getMessage() <<  usersChat->at(2).getLogin()<<std::endl;
		std::cout<<usersChat->at(3).getMessage() <<  usersChat->at(3).getLogin()<<std::endl;
		//cout<<
		//User temp = usersChat->at(i);//.getMessage;
		
		//std::cout<<&usersChat->at(i)<<std::endl;
		//usersChat->at(i)._inMessage = Message;
		//std::cout<<this->_outMessage<<std::endl;
		
		//this->outMessage(Message); //� ���� ��������� ��������� ���������
		//usersChat->inMessage(Message);  //� ������������ �������� ���������- ��������
		//usersChat->at(i).inUser = this;//��������� ���������� �� �����������, �������� ����� ����� ����� �� ���� ������ ���������� ������� ������������		
	//}
	std::cout << "����������� "<<this->getLogin()<<" �������� c�������� ���� ������������� ���� "<<std::endl;
	return 1;		
}

bool operator==(const User &user1,const User &user2){
 	return (user1.getLogin() == user2.getLogin());
	}

class Chat{
private:
	const char *_name;
	int _maxUsers;
public:
	Chat(const char* nameChat, const int max):_name(nameChat), _maxUsers(max){	
		users = new std::vector<User>;
		usersChat = new std::vector<User>;
		std::cout << "��� "<< _name <<" �� "<<_maxUsers<<" ������������� ������"<< std::endl;
	}
	
	bool regUser(User Username);	
	//bool userLogin(User Username);
	bool userLogin(char* login, char* password);	
	bool userlogout(User Username);
	bool delUser(User Username);
	bool getAllUsersChat();
};

	
bool Chat::regUser(User Username){
	if(users->empty()){	
		users -> push_back(Username);
		std::cout << "����������, �� ������������������ ��� ������� "<< Username.getLogin()<< std::endl;
		return 1;
	}
	else{
		for(int i = 0; i < users->size(); ++i){
			if(users->at(i).getLogin() == Username.getLogin()){
			std::cout << "������������ � ����� ������� ��� ����������"<< std::endl;
			return 0;
			}				
		}
		users -> push_back(Username);			
	}
	std::cout << "����������, �� ������������������ ��� ������� "<<Username.getLogin()<< std::endl;
	return 1;
}


/*
bool Chat::userLogin(User Username){
	for(int i = 0; i < usersChat->size(); ++i){
		if(usersChat->at(i).getLogin() == Username.getLogin()){
		std::cout << "������������ � ������� "<<Username.getLogin()<<" ��� �������� ����"<< std::endl;
		return 0;
		}				
	}
	usersChat -> push_back(Username);
	std::cout << "�� ����� � ��� ��� ������� "<<Username.getLogin()<< std::endl;
	return 1;				
}
*/

bool Chat::userLogin(char* login, char* password){
	for(int i = 0; i < usersChat->size(); ++i){
		if(usersChat->at(i).getLogin() == login){
		std::cout << "������������ � ������� "<<login<<" ��� �������� ����"<< std::endl;
		return 0;
		}				
	}
	
	for(int i = 0; i < users->size(); ++i){
		if((users->at(i).getPassword() == password) && (users->at(i).getLogin() == login)){
			usersChat -> push_back(users->at(i));
			std::cout << "�� ����� � ��� ��� ������� "<<users->at(i).getLogin()<< std::endl;
				return 1;	
		}				
	}
	std::cout << "��������� ������ ��������, ���������� �����"<< std::endl;
	
}

	
bool Chat::userlogout(User Username){   
	if(usersChat->empty()){
		std::cout << "� ���� ��� �������������"<< std::endl;
		return 0;}
	for(int i = 0; i < usersChat->size(); ++i){
		if(usersChat->at(i).getLogin() == Username.getLogin()){
			usersChat -> erase(usersChat->begin() +i);
			std::cout << "������������ "<<Username.getLogin() <<" ����� �� ����"<< std::endl;
			return 1;
		}				
	}
	std::cout << "������������ � ������ "<<Username.getLogin()<<" �� ���� � ����"<< std::endl;
	return 0;
}

bool Chat::delUser(User Username){
	if(users->empty()) return 0;
	for(int i = 0; i < users->size(); ++i){
		if(users->at(i).getLogin() == Username.getLogin()){
			users -> erase(users->begin() + i);
			std::cout << "������������ � ������ "<<Username.getLogin()<<" ������"<< std::endl;
			return 1;
		}				
	}
	std::cout << " ������ ������������ �� ����������"<< std::endl;
	return 0;
}
bool Chat::getAllUsersChat(){
	if(users->empty()){ 
		std::cout<<"� ���� ��� �������������"<<std::endl;
		return 0;}
	
	for(int i = 0; i < usersChat->size(); ++i){
		std::cout<<usersChat->at(i).getLogin()<<std::endl;
	}
	return 1;
}

int main() 
{ 
setlocale(LC_ALL, "Russian");

const int sizeNameChat = 30;
int maxUsers;
char nameChat[sizeNameChat];

std::cout <<"������� �������� ��� ����"<< std::endl;
std::cin.getline(nameChat,sizeNameChat);
std::cout <<"������� ������������ ���������� ������������� ����"<< std::endl;
std::cin >> maxUsers;
Chat chat0(nameChat,maxUsers);



User user0("Boba", "Boba", "1212");
User user1("Biba", "Biba", "1213");
User user2("Lupa", "Lupa", "1214");
User user3("Pupa", "Pupa", "1215");

chat0.regUser(user0);
chat0.regUser(user1);
chat0.regUser(user2);
chat0.regUser(user3);

chat0.userLogin("Boba","1111");
chat0.userLogin("Boba","1212");
chat0.userLogin("BIBI", "1213");
chat0.userLogin("Biba","1213");
chat0.userLogin("Pupa","1215");


chat0.getAllUsersChat();

chat0.userLogin("Boba","1111");
chat0.userLogin("Boba","1212");
chat0.userLogin("BIBI", "1213");
chat0.userLogin("Biba","1213");
chat0.userLogin("Pupa","1215");

chat0.userlogout(user0);
chat0.userlogout(user0);
chat0.userlogout(user1);
chat0.userlogout(user2);

chat0.userlogout(user0);
chat0.userlogout(user1);
chat0.userlogout(user2);

chat0.userLogin("Boba","1212");
chat0.userLogin("Biba","1213");
chat0.userLogin("Pupa","1215");
chat0.userLogin("Lupa","1214");


user0.sendMessageUser(user1,"������");
user1.sendMessageUser(user0,"���������");
chat0.userlogout(user1);
user1.getMessageUser();
chat0.userLogin("Biba","1213");
user1.getMessageUser();

user3.sendMessageUser("��� ����!?");

user0.getMessageUser();
user1.getMessageUser();
user2.getMessageUser();
user3.getMessageUser();

		std::cout<<usersChat->at(0).getMessage() << usersChat->at(0).getLogin()<<std::endl;
		std::cout<<usersChat->at(1).getMessage() << usersChat->at(1).getLogin()<< std::endl;
		std::cout<<usersChat->at(2).getMessage() <<  usersChat->at(2).getLogin()<<std::endl;
		std::cout<<usersChat->at(3).getMessage() <<  usersChat->at(3).getLogin()<<std::endl;
		
user0.getMessageUser();
user1.getMessageUser();


//for(int i = 0; i < usersChat->size(); ++i){
//	    std::cout<<&usersChat->at(i)<<std::endl;}


return 0;
}
