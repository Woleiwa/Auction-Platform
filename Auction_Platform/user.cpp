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
using namespace std;
extern mutex u_mtx;
extern User_List ulist;
extern Order_List olist;
extern Commodity_List clist;
extern void Start();
extern void confidential_input(char password[]);
extern bool Judge(char password[20]);

User::User()
{

}

User::User(string id)
{
	ulist.Read_from_txt();
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

void User::Log_in()
{
	system("cls");
	cout << "*******Welcome to User Platform*******" << endl;
	cout << "==============================================================================================================" << endl;
	cout << "instruction:1.seller function 2.consumer function 3.modify information 4.charge 5.check e_mail 6.quit " << endl;
	cout << "==============================================================================================================" << endl;
	cout << "Please input£º";
	int judge;
	cin >> judge;
	while ((judge != 1 && judge != 2 && judge != 3 && judge != 4 && judge != 5 && judge != 6) || cin.fail())
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
		}
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		cout << "******Error input******" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << "==============================================================================================================" << endl;
		cout << "instruction:1.seller function 2.consumer function 3.modify information 4.charge 5.check e_mail 6.quit "<< endl;
		cout << "==============================================================================================================" << endl;
		cout << "Please input£º";
		cin >> judge;
	}
	Seller seller(this->my_inform.id);
	Consumer consumer(this->my_inform.id);
	switch (judge)
	{
	case 1:
		seller.operate();
		this->Log_in();
		break;
	case 2:
		consumer.operate();
		this->Log_in();
		break;
	case 3:
		if (this->Change_information())
		{
			this->Log_in();
		}
		return;
		break;
	case 4:
		if (this->Charge())
		{
			this->Log_in();
		}
		return;
		break;
	case 5:

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

bool User::Change_information()
{
	bool res = true;
	string uid = this->my_inform.id;
	ulist.Read_from_txt();
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
		cout << "Please input£º";
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
		ulist.Write_to_txt();
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
		ulist.Write_to_txt();
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
		ulist.Write_to_txt();
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

			ulist.Write_to_txt();
			cout << "Modify successfully!" << endl;
			Sleep(200);
		}
		else
		{
			this->Freeze();
			res = false;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			cout << "You have been frozen!" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			Sleep(200);
			Start();
		}
	}
	return res;
}

bool User::Charge()
{
	bool res = true;
	char password[20];
	string uid = this->my_inform.id;
	ulist.Read_from_txt();
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
		ulist.Write_to_txt();
	}
	else
	{
		this->Freeze();
		res = false;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		cout << "You have been frozen!" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		Sleep(200);
		Start();
	}
	return res;
}

void User::Freeze()
{
	string uid = this->my_inform.id;
	ulist.Read_from_txt();
	inform_list* pointer = ulist.find_one_user(uid);
	this->my_inform.con = frozen;
	pointer->data.con = frozen;
	ulist.Write_to_txt();
	clist.Read_from_txt();
	clist.freeze_user(this->my_inform.id);
	clist.Write_to_txt();
	olist.Read_from_txt();
	olist.freeze_user(this->my_inform.id);
	olist.Write_to_txt();
}

void User::Thaw()
{
	string uid = this->my_inform.id;
	ulist.Read_from_txt();
	inform_list* pointer = ulist.find_one_user(uid);
	this->my_inform.con = active;
	pointer->data.con = active;
	ulist.Write_to_txt();
}