#pragma once
#include <iostream> 
#include <vector> 
#include <string> 
#include "user.h"
using std::string;
extern char ch;
extern int maxUsers;
extern string name;
extern string login;
extern string pass;
extern string message;
extern string regUser;
extern string inChat ;
extern string outChat ;
extern string exitProg;
extern string listUser;
extern string sendMes;
extern string getMes;
extern string sendMessAll;
extern string ansMes;
extern string delUser;
extern std::vector<User> users;  //������ ���� ������������������ �������������
extern User* curUser;//������ ��������� �� �������� ������������