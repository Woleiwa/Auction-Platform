#pragma once
#ifndef _USER_
#define _USER_
#include<cstring>
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

struct inform_list//��Ϣ����
{
	inform data;
	inform_list* next;
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