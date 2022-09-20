#include"admin.h"
#include"user.h"
#include<windows.h>
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
	User_list ulist;
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

int main()
{
	Start();
	return 0;
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
		cout << endl << "******Error input******" << endl;
		cout << "==============================================================================================================" << endl;
		cout << "instruction£º1.user_login 2.user_regist 3.admin_login 4.forget_password 5.exit" << endl;
		cout << "==============================================================================================================" << endl;
		cout << "Please input your instruction£º";
		cin >> judge;
	}
	if (judge == 1)
	{
		User_list ulist;
		ulist.Read_from_txt();
		ulist.Sign_in();
		Start();
	}
	else if (judge == 2)
	{
		User_list ulist;
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
		User_list ulist;
		ulist.Read_from_txt();
		ulist.Forget_Password();
		ulist.Write_to_txt();
		Start();
	}
	else
	{
		cout << "******See you!******" << endl;
		Sleep(1500);
		return;
	}
}

#endif // _MAIN_
