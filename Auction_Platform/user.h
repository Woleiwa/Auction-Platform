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

struct inform//�û���Ϣ
{
	char id[10] = "\0";
	char name[20] = "\0";
	unsigned int md5_code[4];
	char address[20] = "\0";
	char contact[20] = "\0";
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

	bool Read_from_txt();//��ȡ��Ϣ

	void Write_to_txt();//д����Ϣ

	void Sign_in();//��¼

	void Regist();

	inform_list* get_information();

	inform_list* find_one_user(string uid);

	void Forget_Password();
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

	bool Change_information();

	bool Charge();

	void Freeze();

	inform get_inform();

	void virtual check_order();

	void virtual check_commodity();

	void Thaw();
};
#endif // !_USER_