#include"admin.h"
#include"user.h"
#include"commodity.h"
#include"order.h"
#include"User_List.h"
#include<windows.h>
#include<mutex>
#include<thread>
#include"Order_List.h"
#include"Commodity_List.h"
//#define _TIMETEST_
//#define _USERTEST_
//#define _ADMINTEST_
#define _MAIN_
#ifdef _TIMETEST_
int main()
{
	Time mytime;
	mytime.current_time();
	string time = mytime.time_to_string();
	cout << time;
	my_time st = mytime.string_to_time(time);
	cout << st.year << '-' << st.month << '-' << st.day << ' ' << st.hour << ':' << st.minute << ':' << st.second;
}
#endif // _TIMETEST_

#ifdef _USERTEST_
int main()
{
	User_List ulist;
	ulist.read_from_txt();
	//ulist.user_register();
	ulist.sign_in();
}
#endif // _USERTEST_

#ifdef _ADMINTEST_
int main()
{
	Admin admin;
	admin.admin_operate();
}
#endif // _ADMINTEST_

#ifdef _MAIN_
void start();
void update();
int instruction_input(int mini, int max, string opline);
static const string operate_line = "instruction£º1.user_login 2.user_register 3.admin_login 4.forget_password 5.exit";
mutex o_mtx;
mutex c_mtx;
mutex u_mtx;
bool update_flag = true;
User_List ulist;
Order_List olist;
Commodity_List clist;

int main()
{
	thread t1(start);
	thread t2(update);
	t1.join();
	t2.join();
}

void start()
{
	system("cls");
	cout << "Welcome to my auction platform!" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN );
	cout << "==============================================================================================================" << endl;
	cout << operate_line << endl;
	cout << "==============================================================================================================" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "Please input your instruction£º";
	int judge = instruction_input(1, 5, operate_line);
	if (judge == 1)
	{
		
		ulist.read_from_txt();
		ulist.sign_in();
		start();
	}
	else if (judge == 2)
	{
		ulist.read_from_txt();
		ulist.user_register();
		start();
	}
	else if (judge == 3)
	{
		Admin admin;
		admin.admin_operate();
		start();
	}
	else if (judge == 4)
	{
		ulist.read_from_txt();
		ulist.forget_password();
		ulist.write_to_txt();
		start();
	}
	else
	{
		update_flag = false;
		cout << "******See you!******" << endl;
		Sleep(1500);
		return;
	}
}

void update()
{
	Commodity_List upclist;
	while (update_flag)
	{	
		upclist.read_from_txt();
		if (upclist.update())
		{
			upclist.write_to_txt();
			cout << endl<<"Information updated!" << endl;
		}
		Sleep(128);
	}
}

int instruction_input(int mini, int max, string opline)
{
	int judge;
	cin >> judge;
	while (judge > max || judge < mini|| cin.fail())
	{
		while (cin.fail())
		{
			cin.clear();
			cin.ignore();
		}
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		cout << "******Error input******" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		cout << "==============================================================================================================" << endl;
		cout << opline << endl;
		cout << "==============================================================================================================" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << "Please input your instruction£º";
		cin >> judge;
	}
	return judge;
}

#endif // _MAIN_
