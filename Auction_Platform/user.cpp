#include"user.h"
#include"mail.h"
#include"md5.h"
#include"mytime.h"
#include"order.h"
#include"commodity.h"
#include"seller.h"
#include"consumer.h"
using namespace std;

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

bool Judge(char password[20])
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
	getline(cin, name);
	bool flag = false;

	inform_list* head = user_head;
	while (head)
	{
		if (head->data.name == name)
		{
			cout << "Repeated name! Please choose a new one:";
			getline(cin, name);
			head = user_head;
		}
		else
		{
			head = head->next;
		}
	}

	char password[20];
	cout << "Please input your password(number,letter and captial required, no shorter than 9 characters):"<<endl;

	cin.getline(password, 19);

	while (!Judge(password))
	{
		cout << "Please input an appropriate password:" << endl;
		cin.getline(password, 19);
	}
	
	unsigned int *md5 = MD5_2(password);

	string address;
	cout << "Please input your address:"<<endl;
	getline(cin, address);

	string contact;
	cout << "Please input your phone_number or e_mail:"<<endl;
	getline(cin, contact);

	double money;
	cout << "Please set your initial account:" << endl;
	cin >> money;
	while (money < 0)
	{
		cout << "Please set a correct initial account:" << endl;
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
			if (head->data.con == frozen)
			{
				cout << "Your account has been frozen!" << endl;
				system("pause");
				return;
			}
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
	bool flag = false;
	for (int i = 0; i < 5; i++)
	{
		if (md5[0] == head->data.md5_code[0] && md5[1] == head->data.md5_code[1]
			&& md5[2] == head->data.md5_code[2] && md5[3] == head->data.md5_code[3])
		{
			flag = true;
			break;
		}
		else
		{
			cout<<endl<<"Please input the right password:";
			confidential_input(password);
			md5 = MD5_2(password);
		}
	}
	if (flag == true)
	{
		cout << endl << "You have logged in!";
		Sleep(200);
		User user(id);
		user.Log_in();
	}
	else
	{
		User user(id);
		user.Freeze();
		cout << "You have been frozen!" << endl;
		system("pause");
		return;
	}
}

inform_list* User_list::get_information()
{
	return user_head;
}

inform_list* User_list::find_one_user(string uid)
{
	inform_list* head = this->user_head;
	while (head)
	{
		if (head->data.id == uid)
		{
			return head;
		}
		head = head->next;
	}
	return head;
}

void User_list::Forget_Password()
{
	cout << "Pleas input your account:" << endl;
	string uid;
	cin >> uid;
	inform_list* list = this->user_head;
	while (list)
	{
		if (list->data.id == uid && list->data.con == active)
		{
			cout << "Pleas input your contact:" << endl;
			string contact;
			cin >> contact;
			if (list->data.contact == contact)
			{
				char password[20];
				cout << "Please input your new password(number,letter and captial required, no shorter than 9 characters):" << endl;

				cin.getline(password, 19);

				while (!Judge(password))
				{
					cout << "Please input an appropriate password:" << endl;
					cin.getline(password, 19);
				}

				unsigned int* md5 = MD5_2(password);

				list->data.md5_code[0] = md5[0];
				list->data.md5_code[1] = md5[1];
				list->data.md5_code[2] = md5[2];
				list->data.md5_code[3] = md5[3];
				
			}
			else
			{
				cout << "It doesn't match your information!" << endl;
				system("pause");
				return;
			}
		}
		list = list->next;
	}
	cout << "No such user or your account has been frozen." << endl;
	Sleep(300);
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
		cout << endl << "******Illegal Input******" << endl;
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
	User_list ulist;
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
				cout << endl << "Please input the right password:";
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
			cout << "You have been frozen!" << endl;
			Sleep(200);
		}
	}
	return res;
}

bool User::Charge()
{
	bool res = true;
	char password[20];
	string uid = this->my_inform.id;
	User_list ulist;
	ulist.Read_from_txt();
	inform_list* pointer = ulist.find_one_user(uid);
	cout << "Please input your  password:";
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
			cout << endl << "Please input the right password:";
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
		while (add <= 0)
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
		cout << "You have been frozen!" << endl;
		Sleep(200);
	}
	return res;
}

void User::Freeze()
{
	string uid = this->my_inform.id;
	User_list ulist;
	ulist.Read_from_txt();
	inform_list* pointer = ulist.find_one_user(uid);
	this->my_inform.con = frozen;
	pointer->data.con = frozen;
	ulist.Write_to_txt();
	Commodity_list clist;
	clist.Read_from_txt();
	clist.freeze_user(this->my_inform.id);
	clist.Write_to_txt();
	Order_List olist;
	olist.Read_from_txt();
	olist.freeze_user(this->my_inform.id);
	olist.Write_to_txt();
}

void User::Thaw()
{
	string uid = this->my_inform.id;
	User_list ulist;
	ulist.Read_from_txt();
	inform_list* pointer = ulist.find_one_user(uid);
	this->my_inform.con = active;
	pointer->data.con = active;
	ulist.Write_to_txt();
}