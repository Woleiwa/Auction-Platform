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

void Seller::sellar_operate()
{
	system("cls");
	cout << "******Welcome to Seller Platform******" << endl;
	cout << "==============================================================================================================" << endl;
	cout << "Instruction£º1.Release 2.Check My Commodity 3.Modify 4.Off_shelf 5.Check Order 6.Return" << endl;
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
		cout << "Instruction£º1.Release 2.Check My Commodity 3.Modify 4.Off_shelf 5.Check Order 6.Return" << endl;
		cout << "==================================================================================================================" << endl;
		cout << "Please input£º";
		cin >> judge;
	}
	switch (judge)
	{
	case 1:
		add_commodity();
		sellar_operate();
		break;
	case 2:
		check_my_commodity();
		sellar_operate();
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

void Seller::add_commodity()
{
	string name;
	double price;
	double add_price;
	string description;
	inform my_inform = this->get_inform();

	cout << "Please input the name of your commodity:"<<endl;
	cin >> name;

	cout << "Please input the initial price of your commodity:"<<endl;
	cin >> price;

	cout << "Please input the minimum markup:"<<endl;
	cin >> add_price;

	cout << "Please input the description:"<<endl;
	cin >> description;

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

void Seller::check_my_commodity()
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
		cout << left << setw(12) << "Id" << setw(12) << "Name" << setw(12) << "price" << setw(12) << "markup" << setw(24) << "releasing time" <<setw(12)<<"state";
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
			cout <<endl<< left << setw(12) << head->data.id << setw(12) << head->data.name << setw(12) << head->data.price << setw(12) << head->data.add_price
				<< setw(24) << str_time << setw(12) << state;
			head = head->next;
		}
	}
	system("pause");
}