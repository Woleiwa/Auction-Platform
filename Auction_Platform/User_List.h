#pragma once
#include"user.h"
#ifndef _USERLIST_
#define _USERLIST_
class User_List
{
public:
	User_List();

	~User_List();

	bool Read_from_txt();//��ȡ��Ϣ

	void Write_to_txt();//д����Ϣ

	void Sign_in();//��¼

	void Regist();

	inform_list* get_information();

	inform_list* find_one_user(string uid);

	void Forget_Password();

	void update(string seller_id, string auctioneer_id, double money);
private:
	inform_list* user_head = NULL, * user_tail = NULL;

};

#endif // !_USERLIST_


