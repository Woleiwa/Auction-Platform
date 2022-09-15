#include"admin.h"
#include"user.h"
#include"commodity.h"
#include"mail.h"
#include"mytime.h"
#include"order.h"

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
		cout << endl<<"Please input the right Admin_id:";
		cin >> id;
	}
	char password[20];
	cout << "Please input your password:";
	confidential_input(password);
	string pass = password;
	while (pass != this->password)
	{
		cout << "Please input the right password:";
		confidential_input(password);
		pass = password;
	}
	cout << endl;
}

void Admin::admin_operate()
{
	system("cls");
	cout << "******Welcome to Admin platform******" << endl;
	cout << "=======================================================================================================================" << endl;
	cout << "instruction£º1.check commodities 2.search commodities 3.check orders 4.check users 5.delete users"<<endl
	<<"6.offshelf commodities 7.massages 8.reviews 9.log out" << endl;
	cout << "=======================================================================================================================" << endl;
	cout << "Please input:";
	int judge;
	cin >> judge;
	while ((judge != 1 && judge != 2 && judge != 3 && judge != 4 && judge != 5 && judge != 6 && judge != 7 && judge != 8 && judge != 9) || cin.fail())
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
		}
		system("cls");
		cout << endl << "******Incorrect Input******" << endl;
		cout << "=======================================================================================================================" << endl;
		cout << "instruction£º1.check commodities 2.search commodities 3.check orders 4.check users 5.delete users" << endl
			<< "6.offshelf commodities 7.massages 8.reviews 9.log out" << endl;
		cout << "=======================================================================================================================" << endl;
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
	
		break;
	case 3:
		
		break;
	case 4:
		check_user();
		admin_operate();
		break;
	case 5:
		
		break;
	case 6:
		
		break;
	case 7:
	
		break;
	case 8:
		
		break;
	case 9:
		return;
		break;
	default:
		break;
	}
}

void Admin::check_user()
{
	User_list ulist;
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
	Commodity_list clist;
	clist.Read_from_txt();
	commodity_list* head = clist.admin_check();
	if (head == NULL)
	{
		cout << "Users haven't released any commodity." << endl;
	}
	else
	{
		cout << left << setw(12) << "Id" << setw(12) << "Name" << setw(12) << "price" << setw(12) << "markup" <<setw(12)<<"seller_id"<< setw(24) << "releasing time" << setw(12) << "state";
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
			cout<<endl << left << setw(12) << head->data.id << setw(12) << head->data.name << setw(12) << head->data.price << setw(12) << head->data.add_price
				<< setw(12) << head->data.user_id << setw(24) << str_time << setw(12) << state;
			head = head->next;
		}
	}
	system("pause");
}