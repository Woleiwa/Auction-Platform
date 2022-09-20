#include"seller.h"
#include"mytime.h"
#include"commodity.h"
#include"user.h"
#include<conio.h>
#include<iomanip>
#include<windows.h>

Seller:: ~Seller()
{

}

void Seller::operate()
{
	system("cls");
	cout << "******Welcome to Seller Platform******" << endl;
	cout << "==============================================================================================================" << endl;
	cout << "Instruction£º1.Release 2.Check My Commodity 3.Modify infomation 4.Off_shelf 5.Check Order 6.Return" << endl;
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
		cout << endl << "******Error Input******" << endl;
		cout << "==================================================================================================================" << endl;
		cout << "Instruction£º1.Release 2.Check My Commodity 3.Modify information 4.Off_shelf 5.Check Order 6.Return" << endl;
		cout << "==================================================================================================================" << endl;
		cout << "Please input£º";
		cin >> judge;
	}
	switch (judge)
	{
	case 1:
		add_commodity();
		operate();
		break;
	case 2:
		check_commodity();
		operate();
		break;
	case 3:
		change_commo_information();
		operate();
		break;
	case 4:
		off_shelf();
		operate();
		break;
	case 5:
		check_order();
		operate();
		break;
	case 6:
		return;
		break;
	default:
		break;
	}
}

void Seller::add_commodity()
{
	string name;
	string description;
	inform my_inform = this->get_inform();

	cout << "Please input the name of your commodity:"<<endl;
	while (name.length() == 0)
	{
		getline(cin, name);
	}

	cout << "Please input the description:"<<endl;
	while (description.length() == 0)
	{
		getline(cin, description);
	}

	double price;
	double add_price;

	cout << "Please input the initial price of your commodity:" << endl;
	cin >> price;
	
	while (price < 0)
	{
		cout << "Please set an appropriate price." << endl;
		cin >> price;
	}
	cout << "Please input the minimum markup:" << endl;
	cin >> add_price;

	while (add_price < 0)
	{
		cout << "Please set an appropriate markup:" << endl;
		cin >> add_price;
	}

	string uid = my_inform.id;

	cout << "Please check the information, input 'yes' to add the commodity, and other to cancel:"<<endl;
	string judge;
	cin >> judge;
	if (judge != "yes")
	{
		cout << endl << "You have cancelled your releasion";
		Sleep(200);
		return;
	}
	cout<< endl << "You have released a commodity";
	Sleep(200);
	Commodity mycommodity(name, price, add_price, description, uid);
	mycommodity.Create_commodity();
}

void Seller::check_commodity()
{
	Commodity_list clist;
	clist.Read_from_txt();
	commodity_list* head = clist.seller_check(this->get_inform().id);
	if (head == NULL)
	{
		cout << "You haven't released any commodity." << endl;
	}
	else
	{
		cout << left << setw(12) << "Id" << setw(20) << "Name" << setw(12) << "price" << setw(12) << "markup" << setw(24) << "releasing time" <<setw(12)<<"state";
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
			cout <<endl<< left << setw(12) << head->data.id << setw(20) << head->data.name << setw(12) << head->data.price << setw(12) << head->data.add_price
				<< setw(24) << str_time << setw(12) << state;
			head = head->next;
		}
	}
	system("pause");
}

void Seller::check_order()
{
	Order_List olist;
	olist.Read_from_txt();
	string uid = this->get_inform().id;
	order_list* head = olist.seller_check(uid);
	if (head == NULL)
	{
		cout << "You have no order." << endl;
		system("pause");
		return;
	}
	cout << left << setw(12) << "Order" << setw(12) << "Auctioneer" << setw(12) << "Commodity" << setw(20) << "Commodity name" << setw(12) << "Bid" << setw(24) << "Time" <<setw(20) << "State" << endl;
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
		cout << left << setw(12) << head->data.order_id << setw(12) << head->data.auctioneer << setw(12) << head->data.commodity_id << setw(20) << head->data.commodity_name
			 << setw(12) << head->data.bid << setw(24) << str_time << setw(20) << state << endl;
		head = head->next;
	}
	system("pause");
}

void Seller::change_commo_information()
{
	Commodity_list clist;
	clist.Read_from_txt();
	commodity_list* head = clist.seller_check(this->get_inform().id);
	commodity_list* list = head;
	while (head)
	{
		
	}
}

void Seller::off_shelf()
{
	Commodity_list clist;
	clist.Read_from_txt();
	commodity_list* head = clist.seller_check(this->get_inform().id);
	if (head == NULL)
	{
		cout << "You haven't released any commodity." << endl;

	}
	else 
	{
		commodity_list* list = head;
		while (list)
		{
			if (list->data.st == OnSale)
			{
				cout << list->data.id <<endl;
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
				flag = true;
				break;
			}
			list = list->next;
		}
		if (!flag)
		{
			cout << "You didn't release such a commodity or the commodity has been sold or offshelved." << endl;
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