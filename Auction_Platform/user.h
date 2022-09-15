#pragma once
#ifndef _USER_
#define _USER_
#include<cstring>
#include<iomanip>
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<conio.h>
#include"mytime.h"
using namespace std;

enum User_con { active, frozen};

struct inform//用户信息
{
	char id[10];
	char name[20];
	unsigned int md5_code[4];
	char address[20];
	char contact[20];
	double money;
	my_time register_time;
	User_con con;
};

struct inform_list
{
	inform data;
	inform_list* next;
};

class User_list
{
public:
	User_list();

	~User_list();

	bool Read_from_txt();//读取信息

	void Write_to_txt();//写入信息

	void Sign_in();//登录

	void Regist();

	inform_list* get_information();
	
private:
	inform_list* user_head = NULL, * user_tail = NULL;

};

class User
{
private:
	inform my_inform;
public:
	User();

	User(string id);

	void Log_in();

	void Log_out();

	void Change_information();

	void Charge();

	void Freeze();

	inform get_inform();

	double get_balance();
};
#endif // !_USER_