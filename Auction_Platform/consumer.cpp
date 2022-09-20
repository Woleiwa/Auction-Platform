#include"consumer.h"
#include"commodity.h"

void Consumer::operate()
{
	system("cls");
	cout << "******Welcome to Consumer Platform******" << endl;
	cout << "==============================================================================================================" << endl;
	cout << "Instruction£º1.Auction 2.Check All Commodity 3.Search 4.Check Order 5.Get information 6.Return" << endl;
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
		cout << "Instruction£º1.Auction 2.Check All Commodity 3.Search 4.Check Order 5.Get information 6.Return" << endl;
		cout << "==================================================================================================================" << endl;
		cout << "Please input£º";
		cin >> judge;
	}
	switch (judge)
	{
	case 1:
		Auction();
		operate();
		break;
	case 2:
		check_commodity();
		operate();
		break;
	case 3:

		break;
	case 4:
		check_order();
		operate();
		break;
	case 5:
		get_information();
		operate();
		break;
	case 6:
		return;
		break;
	default:
		break;
	}
}

void Consumer::check_commodity()
{
	Commodity_list clist;
	clist.Read_from_txt();
	commodity_list* head = clist.consumer_check(this->get_inform().id);
	if (head == NULL)
	{
		cout << "There were no commodities for you." << endl;
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
		string judge;
		cout << endl << "Do you want to auction? Input 'yes' to auction."<<endl;
		cin >> judge;
		if (judge != "yes")
		{
			system("pause");
			return;
		}
		else
		{
			cout << endl << "Please input the commodity id you want to auction." << endl;
			string c_id;
			cin >> c_id;
			Auction(c_id);
		}
	}
}

void Consumer::check_order()
{
	Order_List olist;
	olist.Read_from_txt();
	string uid = this->get_inform().id;
	order_list* head = olist.consumer_check(uid);
	if (head == NULL)
	{
		cout << "You have no order." << endl;
		system("pause");
		return;
	}
	cout << left << setw(12) << "Order" << setw(12) << "Seller" << setw(12) << "Commodity" << setw(20) << "Commodity name" << setw(12) << "Bid" << setw(24) << "Time" << setw(20) << "State" << endl;
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
		cout << left << setw(12) << head->data.order_id << setw(12) << head->data.seller_id << setw(12) << head->data.commodity_id << setw(20) << head->data.commodity_name
			<< setw(12) << head->data.bid << setw(24) << str_time << setw(20) << state << endl;
		head = head->next;
	}
	system("pause");
}

void Consumer::Auction()
{
	cout << endl << "Please input the commodity id you want to auction." << endl;
	string c_id;
	cin >> c_id;
	Auction(c_id);
}

void Consumer::Auction(string id)
{
	Commodity commo(id);
	commodity_inform commo_info = commo.my_info();
	if (strlen(commo_info.id) == 0)
	{
		cout << "No such commodity!" << endl;
	}
	else
	{
		Order_List olist;
		olist.Read_from_txt();
		double mininum_price = 0;
		mininum_price = olist.max_price(id);
		cout << "The highest bid now is:" << mininum_price << endl;
		cout << "Its markup is:" << commo_info.add_price << endl;
		cout << "Please input your bid:" << endl;
		double offer;
		cin >> offer;
		while (offer < mininum_price + commo_info.add_price && offer > this->get_inform().money)
		{
			cout << "Please input an aapropriate bid(maybe you don't have enough money):" << endl;
			cin >> offer;
		}
		string seller_id = commo_info.user_id;
		string auctioneer_id = this->get_inform().id;
		string commo_id = commo_info.id;
		string name = commo_info.name;
		Order my_order(seller_id, auctioneer_id, commo_id, name, offer);
		cout << "Input 'yes' to affirm:" << endl;
		string judge;
		cin >> judge;
		if (judge == "yes")
		{
			my_order.add_to_olist();
			cout << "You have made an order!" << endl;
		}
		else
		{
			cout << "Cancelled!" << endl;
		}
	}
	system("pause");
	return;
}

void Consumer::search_commodity()
{

}

void Consumer::get_information()
{
	cout << "Please input the commodity id you want to check:" << endl;
	string cid;
	cin >> cid;
	Commodity_list clist;
	clist.Read_from_txt();
	commodity_inform info = clist.consumer_search_by_id(cid);
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
		cout << "If you want to auction this commodity, please input 'yes':" << endl;
		string judge;
		cin >> judge;
		if (judge == "yes")
		{
			this->Auction(cid);
		}
	}
}