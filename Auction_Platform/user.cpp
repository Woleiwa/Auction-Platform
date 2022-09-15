#include"user.h"
#include"mail.h"
#include"md5.h"
#include"mytime.h"
#include"order.h"
#include"commodity.h"
#include"seller.h"

void confidential_input(char password[])
{
	char ch;
	int index = 0;
	while ((ch = _getch()) != '\r')
	{
		if (ch != '\b')
		{
			cout << "*";
			password[index++] = ch;
		}
		else
		{
			cout << '\b';
			index--;
		}
	}
	password[index++] = '\0';
}

void string_to_md5(string md5, inform& res)
{
	int head = 0;
	int rear = 0;
	rear = md5.find(' ', head);
	string num1(md5, head, rear - head);

	head = rear + 1;
	rear = md5.find(' ', head);
	string num2(md5, head, rear - head);

	head = rear + 1;
	rear = md5.find(' ', head);
	string num3(md5, head, rear - head);

	head = rear + 1;
	rear = md5.length();
	string num4(md5, head, rear - head);

	res.md5_code[0] = (unsigned) stoll(num1);
	res.md5_code[1] = (unsigned) stoll(num2);
	res.md5_code[2] = (unsigned) stoll(num3);
	res.md5_code[3] = (unsigned) stoll(num4);
}

string md5_to_string(inform info)
{
	string num1 = to_string(info.md5_code[0]);
	string num2 = to_string(info.md5_code[1]);
	string num3 = to_string(info.md5_code[2]);
	string num4 = to_string(info.md5_code[3]);
	string res = num1 + ' ' + num2 + ' ' + num3 + ' ' + num4;
	return res;
}

inform string_to_info(string st)
{
	int head = 0;
	int rear = 0;
	rear = st.find(',',head);
	string uid(st, head, rear - head);

	head = rear + 1;
	rear = st.find(',', head);
	string name(st, head, rear - head);

	head = rear + 1;
	rear = st.find(',', head);
	string md5_code(st, head, rear - head);

	head = rear + 1;
	rear = st.find(',', head);
	string address(st, head, rear - head);

	head = rear + 1;
	rear = st.find(',', head);
	string contact(st, head, rear - head);

	head = rear + 1;
	rear = st.find(',', head);
	string money(st, head, rear - head);

	head = rear + 1;
	rear = st.find(',', head);
	string register_time(st, head, rear - head);

	head = rear + 1;
	rear = st.length();
	string state(st, head, rear - head);

	inform res;
	strcpy(res.id , uid.c_str());
	strcpy(res.name, name.c_str());
	strcpy(res.address, address.c_str());
	strcpy(res.contact, contact.c_str());

	res.money = stod(money);
	Time time;
	res.register_time = time.string_to_time(register_time);
	string_to_md5(md5_code, res);
	
	if (state == "active")
	{
		res.con = active;
	}
	else
	{
		res.con = frozen;
	}

	return res;
}

string info_to_string(inform info)
{
	string id = info.id;
	string name = info.name;
	string address = info.address;
	string contact = info.contact;
	Time register_time(info.register_time);
	string time = register_time.time_to_string();
	string money = to_string(info.money);
	string md5 = md5_to_string(info);
	string state;
	if (info.con == active)
	{
		state = "active";
	}
	else
	{
		state = "frozen";
	}
	string res = id + ',' + name + ',' + md5 + ',' + address + ',' + contact + ',' + money + ',' + time + ',' + state;
	return res;
}

User_list::User_list()
{
	
}

User_list::~User_list()
{
	while (this->user_head)
	{
		inform_list* list = this->user_head;
		this->user_head = list->next;
		delete list;
	}
}

bool User_list:: Read_from_txt()
{
	char buffer[256];
	ifstream userfile("user.txt");
	if (!userfile.is_open())
	{
		return false;
	}

	while (!userfile.eof())
	{
		userfile.getline(buffer, 255);
		if (strlen(buffer) <= 1)
		{
			break;
		}

		string info(buffer);
		inform user_info = string_to_info(info);
		if (user_head == NULL)
		{
			user_head = new inform_list;
			user_head->data = user_info;
			user_head->next = NULL;
			user_tail = user_head;
		}
		else
		{
			user_tail->next = new inform_list;
			user_tail = user_tail->next;
			user_tail->data = user_info;
			user_tail->next = NULL;
		}
	}
	return true;
}

void User_list::Write_to_txt()
{
	ofstream userfile("user.txt");
	if (!userfile.is_open())
	{
		return;
	}
	else
	{
		inform_list* head = user_head;
		while (head != NULL)
		{
			string info_str = info_to_string(head->data);
			userfile << info_str + '\n';
			head = head->next;
		}
	}
}

bool judge(char password[20])
{
	
	int length = strlen(password);

	if (length < 9)
	{
		return false;
	}

	bool j1 = false;
	bool j2 = false;
	bool j3 = false;

	for (int i = 0; i < length; i++)
	{
		if (password[i] - '0' <= 9 && password[i] - '0' >= 0)
		{
			j1 = true;
		}
		else if (password[i] - 'a' <= 25 && password[i] - 'a' >= 0)
		{
			j2 = true;
		}
		else if (password[i] - 'A' <= 25 && password[i] - 'A' >= 0)
		{
			j3 = true;
		}
	}
	return(j1 & j2 & j3);
}

void User_list::Regist()
{
	string name;
	cout << "Please input your user_name:";
	cin >> name;
	bool flag = false;

	inform_list* head = user_head;
	while (head)
	{
		if (head->data.name == name)
		{
			cout << "Repeated name! Please choose a new one:";
			cin >> name;
			head = user_head;
		}
		else
		{
			head = head->next;
		}
	}

	char password[20];
	cout << "Please input your password(number,letter and captial required, no shorter than 9 characters):";

	cin >> password;

	while (!judge(password))
	{
		cout << "Please input an appropriate password:";
		cin >> password;
	}
	
	unsigned int *md5 = MD5_2(password);

	string address;
	cout << "Please input your address:";
	cin >> address;

	string contact;
	cout << "Please input your phone_number or e_mail:";
	cin >> contact;

	double money;
	cout << "Please set your initial account:";
	cin >> money;
	while (money < 0)
	{
		cout << "Please set a correct initial account:";
		cin >> money;
	}

	inform new_account;

	if (user_tail == NULL)
	{
		strcpy(new_account.id, "U00001");
	}
	else
	{
		string uid = user_tail->data.id;
		string unum(uid, 1, 5);
		int num = stoi(unum);
		num += 1;
		unum = to_string(num);
		while (unum.length()< 5)
		{
			unum = '0' + unum;
		}
		unum = 'U' + unum;
		strcpy(new_account.id, unum.c_str());
	}

	strcpy(new_account.name, name.c_str());
	new_account.md5_code[0] = md5[0];
	new_account.md5_code[1] = md5[1];
	new_account.md5_code[2] = md5[2];
	new_account.md5_code[3] = md5[3];

	strcpy(new_account.contact, contact.c_str());
	strcpy(new_account.address, address.c_str());

	Time cur;
	new_account.register_time = cur.current_time();

	new_account.money = money;
	
	new_account.con = active;

	if (user_tail == NULL)
	{
		user_tail = new inform_list;
		user_tail->data = new_account;
		user_tail->next = NULL;
		user_head = user_tail;
	}
	else
	{
		user_tail->next = new inform_list;
		user_tail = user_tail->next;
		user_tail->data = new_account;
		user_tail->next = NULL;
	}
	Write_to_txt();
	cout << "You have registed an account! Your user id is :" << new_account.id << endl;
	system("pause");
}

void User_list::Sign_in()
{
	
	inform_list* head = user_head;
	if (head == NULL)
	{
		cout << "No user now!Please regist one!";
		Sleep(1000);
		return;
	}
	string id;
	cout << "Please input your user_id:";
	cin >> id;
	while (head)
	{
		if (head->data.id == id)
		{
			break;
		}
		else
		{
			head = head->next;
		}
		if (head == NULL)
		{
			cout<<endl<< "Please input a correct user_id:";
			cin >> id;
			head = user_head;
		}
	}
	
	char password[20];
	cout << "Please input your password:";
	confidential_input(password);
	unsigned* md5 = MD5_2(password);
	for (int i = 0; i < 5; i++)
	{
		if (md5[0] == head->data.md5_code[0] && md5[1] == head->data.md5_code[1]
			&& md5[2] == head->data.md5_code[2] && md5[3] == head->data.md5_code[3])
		{
			break;
		}
		else
		{
			cout<<endl<<"Please input the right password:";
			confidential_input(password);
			md5 = MD5_2(password);
		}
	}
	cout << endl <<"You have logged in!";
	Sleep(100);
	User user(id);
	user.Log_in();
}

inform_list* User_list::get_information()
{
	return user_head;
}

User::User()
{

}

User::User(string id)
{
	User_list ulist;
	ulist.Read_from_txt();
	inform_list* head = ulist.get_information();
	while (head)
	{
		if (head->data.id == id)
		{
			break;
		}
		else
		{
			head = head->next;
		}
	}
	this->my_inform = head->data;
}

void User::Log_in()
{
	system("cls");
	cout << "*******Welcome to User Platform*******" << endl;
	cout << "============================================================================================" << endl;
	cout << "instruction:1.seller function 2.consumer function 3.modify information 4.check e-mail 5.quit" << endl;
	cout << "============================================================================================" << endl;
	cout << "Please input£º";
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
		cout << "============================================================================================" << endl;
		cout << "instruction:1.seller function 2.consumer function 3.modify information 4.check e-mail 5.quit "<< endl;
		cout << "============================================================================================" << endl;
		cout << "Please input£º";
		cin >> judge;
	}
	Seller seller(this->my_inform.id);
	switch (judge)
	{
	case 1:
		seller.sellar_operate();
		this->Log_in();
		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

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