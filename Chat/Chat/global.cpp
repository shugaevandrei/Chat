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
string regUser = " R- ����������� ������ ������������\n";
string inChat = " I- ����� � ���\n";
string outChat = " O- ����� �� ����\n";
string exitProg = " E- ����� �� ���������\n";
string listUser = " A- ������ �������������\n";
string sendMes = " S- ���������� ��������� ������������\n";
string getMes = " G- �������� ��������� �� ������������\n";
string sendMessAll = " M- ���������� ��������� ��� �������������\n";
string ansMes = " T- �������� ������������ �� �������� ���������\n";
string delUser = " D- ������� ������������\n";
std::vector<User> users;  //������ ���� ������������������ �������������
User* curUser = nullptr;//������ ��������� �� �������� ������������