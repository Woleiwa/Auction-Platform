#include<iomanip>
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<conio.h>
#include"user.h"
#include"User_List.h"
#include"mail.h"
#include"md5.h"
#include"mytime.h"
#include"order.h"
#include"commodity.h"
#include"seller.h"
#include"consumer.h"
#include<mutex>
#include"Commodity_List.h"
#include"Order_List.h"
#include"Mail_List.h"
using namespace std;
extern mutex u_mtx;
extern User_List ulist;
extern Order_List olist;
extern Commodity_List clist;
extern void confidential_input(char password[]);
extern bool Judge(char password[20]);
extern int instruction_input(int mini, int max, string opline);
static const string operate_line = "instruction:1.seller function 2.consumer function 3.modify information 4.charge 5.check massage 6.exit";

User::User()
{

}

User::User(string id)
{
	ulist.read_from_txt();
	inform_list* head = ulist.get_information();
	while (head)
	{
		if (head->data.id == id)
		{
			this->my_inform = head->data;
			break;
		}
		else
		{
			head = head->next;
		}
	}
}

void User::operate()
{
	system("cls");
	cout << "*******Welcome to User Platform*******" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN );
	cout << "==============================================================================================================" << endl;
	cout << operate_line << endl;
	cout << "==============================================================================================================" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "Please input??";
	int judge = instruction_input(1,6,operate_line);
	Seller seller(this->my_inform.id);
	Consumer consumer(this->my_inform.id);
	switch (judge)
	{
	case 1:
		seller.operate();
		this->operate();
		break;
	case 2:
		consumer.operate();
		this->operate();
		break;
	case 3:
		if (this->modify_information())
		{
			this->operate();
		}
		return;
		break;
	case 4:
		if (this->charge())
		{
			this->operate();
		}
		return;
		break;
	case 5:
		this->check_mail();
		this->operate();
		break;
	case 6:
		return;
		break;
	default:
		break;
	}
}

inform User::get_inform()
{
	return this->my_inform;
}

void User::check_order()
{

}

void User::check_commodity() 
{

}

bool User::modify_information()
{
	bool res = true;
	string uid = this->my_inform.id;
	ulist.read_from_txt();
	inform_list* pointer = ulist.find_one_user(uid);
	cout << "My user id:" << this->my_inform.id << endl;
	cout << "My user name:" << this->my_inform.name << endl;
	cout << "My address:" << this->my_inform.address << endl;
	cout << "My contact:" << this->my_inform.contact << endl;

	cout << "==============================================================================================================" << endl;
	cout << "Input 1 to modify name, 2 to modify address, 3 to modify contact, 4 to modify password, 5 to exit" << endl;
	cout << "==============================================================================================================" << endl;
	int judge;
	cin >> judge;
	while ((judge != 1 && judge != 2 && judge != 3 && judge != 4 && judge != 5) || cin.fail())
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
		}
		cout << endl << "******Illegal Input******" << endl;
		cout << "==============================================================================================================" << endl;
		cout << "Input 1 to modify name, 2 to modify address, 3 to modify contact, 4 to modify password, 5 to exit" << endl;
		cout << "==============================================================================================================" << endl;
		cout << "Please input??";
		cin >> judge;
	}
	if (judge == 1)
	{
		cout << "Please input yout new name:" << endl;
		string new_name;
		while (new_name.length() == 0)
		{
			getline(cin, new_name);
		}
		inform_list* head = ulist.get_information();
		while (head)
		{
			if (head->data.name == new_name)
			{
				cout << "Repeated name! Please choose a new one:";
				getline(cin, new_name);
				head = ulist.get_information();
			}
			head = head->next;

		}
		strcpy(this->my_inform.name, new_name.c_str());
		strcpy(pointer->data.name, new_name.c_str());
		ulist.write_to_txt();
		cout << "Modify successfully!" << endl;
		Sleep(200);
	}
	else if (judge == 2)
	{
		string new_address;
		cout << "Please input yout new address:" << endl;
		while (new_address.length() == 0)
		{
			getline(cin, new_address);
		}
		strcpy(this->my_inform.address, new_address.c_str());
		strcpy(pointer->data.address, new_address.c_str());
		ulist.write_to_txt();
		cout << "Modify successfully!" << endl;
		Sleep(200);
	}
	else if (judge == 3)
	{
		string new_contact;
		cout << "Please input yout new contact:" << endl;
		while (new_contact.length() == 0)
		{
			getline(cin, new_contact);
		}
		strcpy(this->my_inform.contact, new_contact.c_str());
		strcpy(pointer->data.contact, new_contact.c_str());
		ulist.write_to_txt();
		cout << "Modify successfully!" << endl;
		Sleep(200);
	}
	else if (judge == 4)
	{
		char password[20];
		cout << "Please input your original password:";
		confidential_input(password);
		unsigned* md5 = MD5_2(password);
		bool flag = false;
		for (int i = 0; i < 5; i++)
		{
			if (md5[0] == pointer->data.md5_code[0] && md5[1] == pointer->data.md5_code[1]
				&& md5[2] == pointer->data.md5_code[2] && md5[3] == pointer->data.md5_code[3])
			{
				flag = true;
				break;
			}
			else
			{
				cout << endl << "Please input the right password(You have " <<5 - i<<" time left):";
				confidential_input(password);
				md5 = MD5_2(password);
			}
		}
		if (flag == true)
		{
			char password[20] = "\0";
			cout << endl <<"Please input your new password(number,letter and captial required, no shorter than 9 characters):" << endl;
			while (strlen(password) == 0)
			{
				cin.getline(password, 19);
			}
			
			while (!Judge(password))
			{
				cout << endl <<"Please input an appropriate password:" << endl;
				cin.getline(password, 19);
			}

			unsigned int* md5 = MD5_2(password);
			this->my_inform.md5_code[0] = md5[0];
			this->my_inform.md5_code[1] = md5[1];
			this->my_inform.md5_code[2] = md5[2];
			this->my_inform.md5_code[3] = md5[3];

			pointer->data.md5_code[0] = md5[0];
			pointer->data.md5_code[1] = md5[1];
			pointer->data.md5_code[2] = md5[2];
			pointer->data.md5_code[3] = md5[3];

			ulist.write_to_txt();
			cout << "Modify successfully!" << endl;
			Sleep(200);
		}
		else
		{
			this->freeze();
			res = false;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			cout << "You have been frozen!" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			Sleep(200);
		}
	}
	return res;
}

bool User::charge()
{
	bool res = true;
	char password[20];
	string uid = this->my_inform.id;
	ulist.read_from_txt();
	inform_list* pointer = ulist.find_one_user(uid);
	cout << "Please input your  password:"<<endl;
	confidential_input(password);
	unsigned* md5 = MD5_2(password);
	bool flag = false;
	for (int i = 0; i < 5; i++)
	{
		if (md5[0] == pointer->data.md5_code[0] && md5[1] == pointer->data.md5_code[1]
			&& md5[2] == pointer->data.md5_code[2] && md5[3] == pointer->data.md5_code[3])
		{
			flag = true;
			break;
		}
		else
		{
			cout << endl << "Please input the right password(You have " << 5 - i << " time left):" << endl;
			confidential_input(password);
			md5 = MD5_2(password);
		}
	}
	if (flag == true)
	{
		cout << endl <<"Your account:" << this->my_inform.money << endl;
		double add;
		cout << "Please input the amount you want to charge:" << endl;
		cin >> add;
		while (add < 0)
		{
			cout << "Please input an appropriate number:" << endl;
			cin >> add;
		}
		this->my_inform.money += add;
		pointer->data.money += add;
		ulist.write_to_txt();
	}
	else
	{
		this->freeze();
		res = false;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		cout << "You have been frozen!" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		Sleep(200);
	}
	return res;
}

void User::freeze()
{
	string uid = this->my_inform.id;
	ulist.read_from_txt();
	inform_list* pointer = ulist.find_one_user(uid);
	this->my_inform.con = frozen;
	pointer->data.con = frozen;
	ulist.write_to_txt();
	clist.read_from_txt();
	clist.freeze_user(this->my_inform.id);
	clist.write_to_txt();
	olist.read_from_txt();
	olist.freeze_user(this->my_inform.id);
	olist.write_to_txt();
}

void User::thaw()
{
	string uid = this->my_inform.id;
	ulist.read_from_txt();
	inform_list* pointer = ulist.find_one_user(uid);
	this->my_inform.con = active;
	pointer->data.con = active;
	ulist.write_to_txt();
}

void User::check_mail()
{
	contacter* head = NULL;
	ulist.read_from_txt();
	string uid = this->my_inform.id;
	head = ulist.my_contacter(uid);
	contacter* list = head;
	cout << "Admin" << endl;
	while (list)
	{
		cout << list->uid << endl;
		list = list->next;
	}
	cout << "Please input the people you want to send massage to:" << endl;
	string receiver;
	cin >> receiver;
	bool flag = false;
	if (receiver == "Admin")
	{
		flag = true;
	}
	else
	{
		list = head;
		while (list)
		{
			if (list->uid == receiver)
			{
				flag = true;
				break;
			}
			list = list->next;
		}
	}
	if (!flag)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		cout << "No such user!" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		system("pause");
		return;
	}
	while (flag)
	{
		Mail_List mlist(uid, receiver);
		mlist.read_from_txt();
		system("cls");
		mail_list* mhead = mlist.get_mails();
		while (mhead)
		{
			Mail cur_mail(uid, receiver, mhead->data);
			cur_mail.print_mail(uid);
			mhead = mhead->next;
		}
		mlist.read_mails(uid);
		mlist.write_to_txt();
		cout << "If you want to send a massage, please input 'yes':" << endl;
		string judge;
		cin >> judge;
		if (judge == "yes")
		{
			string content;
			cout << "Please input your massage:" << endl;
			cin >> content;
			Mail new_mail(uid, receiver, content);
			new_mail.add_to_list();
		}
		else
		{
			flag = false;
		}
	}
	system("pause");
	return;
}