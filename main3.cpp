#include <iostream> 
#include <vector> 

class User{
private:
	const char *_name;
	const char *_login;
	const char *_password;
	
	char *_outMessage = NULL; //хранение исхоядщего сообщения
	char *_inMessage = NULL; //хранение входящего сообщения
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
	bool getMessageUser();//получить входящее сообщение от другого пользователя
	bool sendMessageUser(User& user, char *Message);//отправить сообщение пользователю
	bool sendMessageUser(char *Message);//отправить сообщение всем пользователям чата
	friend bool operator==(const User &user1, const User &user2);
};

std::vector<User> *users = NULL;  //Вектор всех зарегистрированных пользователей
std::vector<User> *usersChat= NULL;  //Вектор вошедших в чат

bool User::sendMessageUser(User &user, char *Message){
	
	for(int i = 0; i < usersChat->size(); ++i){
		if(usersChat->at(i).getLogin() == this->getLogin()) {//проверка, есть ли чате ли сам пользователь желающий отправить сообщение	
			for(int i = 0; i < usersChat->size(); ++i){	
				if(usersChat->at(i).getLogin() == user.getLogin()){
					this->outMessage(Message); //у себя сохраняем исходящее сообщение
					user.inMessage(Message);  //у пользователя которому отправили- входящее
					user.inUser = this;//сохраняем информацию об отправителе, допустим потом можно будет по этой ссылке посмотреть профиль пользователя			
					std::cout <<this->getLogin() << ": сообщение \""<<user._inMessage <<"\" отправлено пользователю "<<user.getLogin()<< std::endl;
					return 1;
				}
			}
			std::cout << "Пользователя с таким логином не существует"<< std::endl;
			return 0;		
		}
		
	}
	std::cout << "Прежде чем отправить сообщение, вам необходимо войти в чат"<< std::endl;
	return 0;			
}
bool User::getMessageUser(){
	if(this->getMessage() == NULL){
		std::cout << "Входящих сообщений нет" << std::endl;
		return 0;}
	
	for(int i = 0; i < usersChat->size(); ++i){
		if(usersChat->at(i).getLogin() == this->getLogin()){//проверка, есть ли чате ли сам пользователь желающий прочитать сообщение		
			std::cout<<this->getLogin() <<": последнее сообщение: \""<<this->getMessage() <<"\" было от пользователя " <<inUser->getLogin()<<std::endl;
			return 1;	
		}
	}
	std::cout <<this->getLogin()<< ": прежде чем прочитать сообщение, вам необходимо войти в чат"<< std::endl;
	return 0;
}
bool User::sendMessageUser(char *Message){
	if(usersChat->empty()){
		std::cout << "В чате нет пользователей"<< std::endl;
		return 0;
	}
	//user.inMessage(Message);  //у пользователя которому отправили- входящее
	//user.inUser = this;//сохраняем информацию об отправителе, допустим потом можно будет по этой ссылке посмотреть профиль пользователя	
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
		
		//this->outMessage(Message); //у себя сохраняем исходящее сообщение
		//usersChat->inMessage(Message);  //у пользователя которому отправили- входящее
		//usersChat->at(i).inUser = this;//сохраняем информацию об отправителе, допустим потом можно будет по этой ссылке посмотреть профиль пользователя		
	//}
	std::cout << "польователь "<<this->getLogin()<<" отправил cообщение всем пользователям чата "<<std::endl;
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
		std::cout << "Чат "<< _name <<" на "<<_maxUsers<<" пользователей создан"<< std::endl;
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
		std::cout << "Поздравляю, вы зарегестрировались под логином "<< Username.getLogin()<< std::endl;
		return 1;
	}
	else{
		for(int i = 0; i < users->size(); ++i){
			if(users->at(i).getLogin() == Username.getLogin()){
			std::cout << "Пользователь с таким логином уже существует"<< std::endl;
			return 0;
			}				
		}
		users -> push_back(Username);			
	}
	std::cout << "Поздравляю, вы зарегестрировались под логином "<<Username.getLogin()<< std::endl;
	return 1;
}


/*
bool Chat::userLogin(User Username){
	for(int i = 0; i < usersChat->size(); ++i){
		if(usersChat->at(i).getLogin() == Username.getLogin()){
		std::cout << "Пользователь с логином "<<Username.getLogin()<<" уже выполнил вход"<< std::endl;
		return 0;
		}				
	}
	usersChat -> push_back(Username);
	std::cout << "Вы вошли в чат под логином "<<Username.getLogin()<< std::endl;
	return 1;				
}
*/

bool Chat::userLogin(char* login, char* password){
	for(int i = 0; i < usersChat->size(); ++i){
		if(usersChat->at(i).getLogin() == login){
		std::cout << "Пользователь с логином "<<login<<" уже выполнил вход"<< std::endl;
		return 0;
		}				
	}
	
	for(int i = 0; i < users->size(); ++i){
		if((users->at(i).getPassword() == password) && (users->at(i).getLogin() == login)){
			usersChat -> push_back(users->at(i));
			std::cout << "Вы вошли в чат под логином "<<users->at(i).getLogin()<< std::endl;
				return 1;	
		}				
	}
	std::cout << "Введенные данные ошибочны, попробуйте снова"<< std::endl;
	
}

	
bool Chat::userlogout(User Username){   
	if(usersChat->empty()){
		std::cout << "В чате нет пользователей"<< std::endl;
		return 0;}
	for(int i = 0; i < usersChat->size(); ++i){
		if(usersChat->at(i).getLogin() == Username.getLogin()){
			usersChat -> erase(usersChat->begin() +i);
			std::cout << "пользователь "<<Username.getLogin() <<" вышел из чата"<< std::endl;
			return 1;
		}				
	}
	std::cout << "Пользователя с именем "<<Username.getLogin()<<" не было в чате"<< std::endl;
	return 0;
}

bool Chat::delUser(User Username){
	if(users->empty()) return 0;
	for(int i = 0; i < users->size(); ++i){
		if(users->at(i).getLogin() == Username.getLogin()){
			users -> erase(users->begin() + i);
			std::cout << "Пользователь с именем "<<Username.getLogin()<<" удален"<< std::endl;
			return 1;
		}				
	}
	std::cout << " Такого пользователя не существует"<< std::endl;
	return 0;
}
bool Chat::getAllUsersChat(){
	if(users->empty()){ 
		std::cout<<"В чате нет пользователей"<<std::endl;
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

std::cout <<"Введите название для чата"<< std::endl;
std::cin.getline(nameChat,sizeNameChat);
std::cout <<"Введите максимальное количество пользователей чата"<< std::endl;
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


user0.sendMessageUser(user1,"привет");
user1.sendMessageUser(user0,"ППППривет");
chat0.userlogout(user1);
user1.getMessageUser();
chat0.userLogin("Biba","1213");
user1.getMessageUser();

user3.sendMessageUser("Как дела!?");

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
