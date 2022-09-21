#include"admin.h"
#include"user.h"
#include"commodity.h"
#include"mail.h"
#include"mytime.h"
#include"order.h"
#include<windows.h>
#include"User_List.h"
#include"Order_List.h"
#include"Commodity_List.h"
extern User_List ulist;
extern Order_List olist;
extern Commodity_List clist;
static void confidential_input(char password[])
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

Admin::Admin()
{
	string id;
	cout << "Please input your Admin_id:";
	cin >> id;
	while (id != this->user_id)
	{
		cout << endl<<"Please input the right Admin_id:" <<endl;
		cin >> id;
	}
	char password[20];
	cout << "Please input your password:" << endl;
	confidential_input(password);
	string pass = password;
	while (pass != this->password)
	{
		cout << "Please input the right password:" << endl;
		confidential_input(password);
		pass = password;
	}
	cout << endl;
}

void Admin::admin_operate()
{
	system("cls");
	cout << "******Welcome to Admin platform******" << endl;
	cout << "==============================================================================================================" << endl;
	cout << "instruction£º1.check commodities 2.search commodities 3.check orders 4.check users 5.freeze users"<<endl
		 << "6.thaw users 7.offshelf commodities 8.commodity information 9.massages 10.log out" << endl;
	cout << "==============================================================================================================" << endl;
	cout << "Please input:";
	int judge;
	cin >> judge;
	while ((judge != 1 && judge != 2 && judge != 3 && judge != 4 && judge != 5 && judge != 6 && judge != 7 && judge != 8 && judge != 9 && judge != 10) || cin.fail())
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
		cout << "instruction£º1.check commodities 2.search commodities 3.check orders 4.check users 5.freeze users" << endl
			 << "6.thaw users 7.offshelf commodities 8.commodity information 9.massages 10.log out" << endl;
		cout << "==============================================================================================================" << endl;
		cout << "Please input:";
		cin >> judge;
	}
	switch (judge)
	{
	case 1:
		check_commodity();
		admin_operate();
		break;
	case 2:
		search();
		admin_operate();
		break;
	case 3:
		check_order();
		admin_operate();
		break;
	case 4:
		check_user();
		admin_operate();
		break;
	case 5:
		freeze_user();
		admin_operate();
		break;
	case 6:
		thaw_user();
		admin_operate();
		break;
	case 7:
		off_shelf();
		admin_operate();
		break;
	case 8:
		get_information();
		admin_operate();
		break;
	case 9:
		
		break;
	case 10:

		break;
	default:
		break;
	}
}

void Admin::check_user()
{
	ulist.Read_from_txt();
	inform_list* head = ulist.get_information();
	cout << left << setw(12) << "User_id" << setw(12) << "Name" << setw(12) << "Address" 
		<< setw(12) << "Contact" << setw(16) << "Balance" << setw(24) << "Regist_time" << setw(12) << "State"<< endl;
	cout << "=============================================================================================" << endl;
	while (head)
	{
		Time time(head->data.register_time);
		string str_time = time.time_to_string();
		string state = "active";
		if (head->data.con == frozen)
		{
			state = "frozen";
		}
		cout << left << setw(12) << head->data.id << setw(12) << head->data.name << setw(12) 
			<< head->data.address << setw(12) << head->data.contact << setw(16) << head->data.money << setw(24) 
			<< str_time << setw(12) << state << endl;
		head = head->next;
	}
	system("pause");
}

void Admin::check_commodity()
{
	clist.Read_from_txt();
	commodity_list* head = clist.admin_check();
	if (head == NULL)
	{
		cout << "Users haven't released any commodity." << endl;
	}
	else
	{
		cout << left << setw(12) << "Id" << setw(20) << "Name" << setw(12) << "price" << setw(12) << "markup" <<setw(12)<<"seller_id"<< setw(24) << "releasing time" << setw(12) << "state";
		while (head)
		{
			Time time(head->data.auction_time);
			string str_time = time.time_to_string();
			string state = "OnSale";
			if (head->data.st == Sold)
			{
				state = "Sold";
			}
			else if (head->data.st == OffShelf)
			{
				state = "OffShelf";
			}
			cout<<endl << left << setw(12) << head->data.id << setw(20) << head->data.name << setw(12) << head->data.price << setw(12) << head->data.add_price
				<< setw(12) << head->data.user_id << setw(24) << str_time << setw(12) << state;
			head = head->next;
		}
	}
	system("pause");
}

void Admin::check_order()
{
	olist.Read_from_txt();
	order_list* head = olist.admin_check();
	if (head == NULL)
	{
		cout << "There is no order." << endl;
		system("pause");
		return;
	}
	cout << left << setw(12) << "Order" << setw(12) << "Seller"<< setw(12) << "Auctioneer" << setw(12) << "Commodity" << setw(20) << "Commodity name" << setw(12) << "Bid" << setw(24) << "Time" << setw(12) << "State" << endl;
	while (head)
	{
		string state = "Waiting";
		if (head->data.st == Deal)
		{
			state = "Deal";
		}
		else if (head->data.st == Cancel)
		{
			state = "Cancel";
		}
		Time time(head->data.time);
		string str_time = time.time_to_string();
		cout << left << setw(12) << head->data.order_id << setw(12)<< head->data.seller_id << setw(12) << head->data.auctioneer << setw(12) << head->data.commodity_id << setw(20) << head->data.commodity_name
			<< setw(12) << head->data.bid << setw(24) << str_time  << setw(12) << state << endl;
		head = head->next;
	}
	system("pause");
}

void Admin::off_shelf()
{
	clist.Read_from_txt();
	commodity_list* head = clist.admin_check();
	if (head == NULL)
	{
		cout << "Users haven't released any commodity." << endl;

	}
	else
	{
		commodity_list* list = head;
		while (list)
		{
			if (list->data.st == OnSale)
			{
				cout << list->data.id << endl;
			}
			list = list->next;
		}
		cout << "Please input the id of the commodity you want to off_shelf:" << endl;
		string id;
		cin >> id;
		list = head;
		bool flag = false;
		while (list)
		{
			if (list->data.st == OnSale && list->data.id == id)
			{
				break;
				flag = true;
			}
			list = list->next;
		}
		if (!flag)
		{
			cout << "Users didn't release such a commodity or the commodity has been sold or offshelved." << endl;
		}
		else
		{
			cout << "Input 'yes' to affirm:" << endl;
			string judge;
			cin >> judge;
			if (judge == "yes")
			{
				Commodity com(id);
				com.offshelf();
				cout << "You have off shelved an commodity:" << id << endl;
			}
			else
			{
				cout << "Cancelled." << endl;
			}
		}
	}
	system("pause");
	return;
}

void Admin::freeze_user()
{
	ulist.Read_from_txt();
	inform_list* head = ulist.get_information();
	inform_list* list = head;
	bool flag = false;
	while (head)
	{
		if (head->data.con == active)
		{
			cout << head->data.id << endl;
			flag = true;
		}
		head = head->next;
	}
	if (!flag)
	{
		cout << "There was no active users." << endl;
		system("pause");
		return;
	}
	cout << "Please input the user id you want to freeze:" << endl;
	string uid;
	cin >> uid;
	flag = false;
	head = list;
	while (head)
	{
		if (head->data.id == uid && head->data.con == active)
		{
			flag = true;
			break;
		}
		head = head->next;
	}
	if (!flag)
	{
		cout << "No such user" << endl;
		system("pause");
		return;
	}
	User user(uid);
	cout << "Input 'yes' to affirm:" << endl;
	string judge;
	cin >> judge;
	if (judge == "yes")
	{
		user.Freeze();
		cout << "Freeze successfully!" << endl;
	}
	else
	{
		cout << "Cancelled" << endl;
	}
	system("pause");
	return;
}

void Admin::thaw_user()
{
	ulist.Read_from_txt();
	inform_list* head = ulist.get_information();
	inform_list* list = head;
	bool flag = false;
	while (head)
	{
		if (head->data.con == frozen)
		{
			cout << head->data.id << endl;
			flag = true;
		}
		head = head->next;
	}
	if (!flag)
	{
		cout << "There was no frozen users." << endl;
		system("pause");
		return;
	}
	cout << "Please input the user id you want to thaw:" << endl;
	string uid;
	cin >> uid;
	flag = false;
	head = list;
	while (head)
	{
		if (head->data.id == uid && head->data.con == frozen)
		{
			flag = true;
			break;
		}
		head = head->next;
	}
	if (!flag)
	{
		cout << "No such user" << endl;
		system("pause");
		return;
	}
	User user(uid);
	cout << "Input 'yes' to affirm:" << endl;
	string judge;
	cin >> judge;
	if (judge == "yes")
	{
		user.Thaw();
		cout << "Thaw successfully!" << endl;
	}
	else
	{
		cout << "Cancelled" << endl;
	}
	system("pause");
	return;
}

void Admin::get_information()
{
	cout << "Please input the commodity id you want to check:" << endl;
	string cid;
	cin >> cid;
	clist.Read_from_txt();
	commodity_inform info = clist.admin_search_by_id(cid);
	if (strlen(info.id) == 0)
	{
		cout << "No such commodity!" << endl;
		system("pause");
		return;
	}
	else
	{
		cout << "Commodity id:" << info.id << endl;
		cout << "Commodity name:" << info.name << endl;
		cout << "Commodity price:" << info.price << endl;
		cout << "Commodity markup:" << info.add_price << endl;
		cout << "Commodity description:" << info.description << endl;
		Time time(info.auction_time);
		string str_time = time.time_to_string();
		cout << "On shelf time:" << str_time << endl;
		string state = "OnSale";
		if (info.st == Sold) 
		{
			state = "Sold";
		}
		else if (info.st == OffShelf)
		{
			state = "OffShelf";
		}
		cout << "State:" << state << endl;
		system("pause");
	}
}

void Admin::search()
{
	cout << "Please input your key words:" << endl;
	string key_words;
	while (key_words.length() == 0)
	{
		getline(cin, key_words);
	}
	commodity_list* head = NULL;
	clist.Read_from_txt();
	head = clist.admin_search_by_key_word(key_words);
	if (head == NULL)
	{
		cout << "Users haven't released any relevant commodity." << endl;
	}
	else
	{
		cout << left << setw(12) << "Id" << setw(20) << "Name" << setw(12) << "price" << setw(12) << "markup" << setw(12) << "seller_id" << setw(24) << "releasing time" << setw(12) << "state";
		while (head)
		{
			Time time(head->data.auction_time);
			string str_time = time.time_to_string();
			string state = "OnSale";
			if (head->data.st == Sold)
			{
				state = "Sold";
			}
			else if (head->data.st == OffShelf)
			{
				state = "OffShelf";
			}
			cout << endl << left << setw(12) << head->data.id << setw(20) << head->data.name << setw(12) << head->data.price << setw(12) << head->data.add_price
				<< setw(12) << head->data.user_id << setw(24) << str_time << setw(12) << state;
			head = head->next;
		}
	}
	system("pause");
}