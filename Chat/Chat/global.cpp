#pragma once
#include <iostream> 
#include <vector> 
#include <string> 
#include "user.h"
using std::string;

char ch;
int maxUsers;
string name;
string login;
string pass;
string message;
string regUser = " R- регистрация нового пользователя\n";
string inChat = " I- войти в чат\n";
string outChat = " O- выйти из чата\n";
string exitProg = " E- выход из программы\n";
string listUser = " A- список пользователей\n";
string sendMes = " S- сотправить сообщение пользователю\n";
string getMes = " G- получить сообщение от пользователя\n";
string sendMessAll = " M- сотправить сообщение все пользователям\n";
string ansMes = " T- ответить пользователю на вхоядщее сообщение\n";
string delUser = " D- удалить пользователя\n";
std::vector<User> users;  //Вектор всех зарегистрированных пользователей
User* curUser = nullptr;//храним указатель на текущего пользователя