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
	ulist.Read_from_txt();
	//ulist.Regist();
	ulist.Sign_in();
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
void Start();
void Update();
mutex o_mtx;
mutex c_mtx;
mutex u_mtx;
bool update = true;
User_List ulist;
Order_List olist;
Commodity_List clist;

int main()
{
	thread t1(Start);
	thread t2(Update);
	t1.join();
	t2.join();
}

void Start()
{
	system("cls");
	cout << "Welcome to my auction platform!" << endl;
	cout << "==============================================================================================================" << endl;
	cout << "instruction£º1.user_login 2.user_regist 3.admin_login 4.forget_password 5.exit" << endl;
	cout << "==============================================================================================================" << endl;
	cout << "Please input your instruction£º";
	int judge;
	cin >> judge;
	while ((judge != 1 && judge != 2 && judge != 3 && judge != 4 && judge != 5) || cin.fail())
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
		cout << "instruction£º1.user_login 2.user_regist 3.admin_login 4.forget_password 5.exit" << endl;
		cout << "==============================================================================================================" << endl;
		cout << "Please input your instruction£º";
		cin >> judge;
	}
	if (judge == 1)
	{
		
		ulist.Read_from_txt();
		ulist.Sign_in();
		Start();
	}
	else if (judge == 2)
	{
		ulist.Read_from_txt();
		ulist.Regist();
		Start();
	}
	else if (judge == 3)
	{
		Admin admin;
		admin.admin_operate();
		Start();
	}
	else if (judge == 4)
	{
		ulist.Read_from_txt();
		ulist.Forget_Password();
		ulist.Write_to_txt();
		Start();
	}
	else
	{
		update = false;
		cout << "******See you!******" << endl;
		Sleep(1500);
		return;
	}
}

void Update()
{
	Commodity_List upclist;
	while (update)
	{	
		upclist.Read_from_txt();
		if (upclist.update())
		{
			upclist.Write_to_txt();
			cout << endl<<"Information updated!" << endl;
		}
		Sleep(128);
	}
	
}
#endif // _MAIN_
