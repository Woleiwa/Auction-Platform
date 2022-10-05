#include "mail.h"
#include "Mail_List.h"
#include <windows.h>
#include<iomanip>
Mail::Mail(string sender, string receiver, string content)
{
	if (strcmp(sender.c_str(), receiver.c_str()) < 0)
	{
		this->data.direction = true;
		this->u1 = sender;
		this->u2 = receiver;
	}
	else
	{
		this->data.direction = false;
		this->u1 = receiver;
		this->u2 = sender;
	}
	strcpy(this->data.massage, content.c_str());
	Time time;
	this->data.time = time.current_time();
	this->data.state = unread;
}

Mail::Mail(string sender, string receiver, mail data)
{
	if (strcmp(sender.c_str(), receiver.c_str()) < 0)
	{
		this->data.direction = true;
		this->u1 = sender;
		this->u2 = receiver;
	}
	else
	{
		this->data.direction = false;
		this->u1 = receiver;
		this->u2 = sender;
	}
	this->data = data;
}

void Mail::add_to_list()
{
	Mail_List mlist(this->u1, this->u2);
	mlist.read_from_txt();
	mlist.add_mail(this->data);
	mlist.write_to_txt();
}

void Mail::print_mail(string uid)
{
	bool reader = (this->u1 == uid);
	Time time(this->data.time);
	string str_time = time.time_to_string();
	string sender_id = this->u1;
	if (uid == this->u1)
	{
		sender_id = this->u2;
	}
	if (reader == this->data.direction)
	{
		cout << left << str_time << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		cout << left << uid + ':' << this->data.massage << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	else
	{
		cout << left << str_time << endl;
		if (this->data.state == unread)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			cout << left << sender_id + ':' << this->data.massage << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			cout << left << sender_id + ':' << this->data.massage << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
	}
}