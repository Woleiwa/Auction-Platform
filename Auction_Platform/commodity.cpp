#include "commodity.h"

Commodity_list::Commodity_list()
{

}

Commodity_list::~Commodity_list()
{
	while (head)
	{
		commodity_list* cur = head;
		head = head->next;
		delete cur;
	}
}

static commodity_inform string_to_info(string str_info)
{
	int head = 0;
	int rear = 0;
	rear = str_info.find(',', head);
	string id(str_info, head, rear - head);

	head = rear + 1;
	rear = str_info.find(',', head);
	string name(str_info, head, rear - head);

	head = rear + 1;
	rear = str_info.find(',', head);
	string price(str_info, head, rear - head);

	head = rear + 1;
	rear = str_info.find(',', head);
	string add_pirce(str_info, head, rear - head);

	head = rear + 1;
	rear = str_info.find(',', head);
	string str_time(str_info, head, rear - head);

	head = rear + 1;
	rear = str_info.find(',', head);
	string user_id(str_info, head, rear - head);

	head = rear + 1;
	rear = str_info.find(',', head);
	string st(str_info, head, rear - head);

	head = rear + 1;
	rear = str_info.length();
	string description(str_info, head, rear - head);

	commodity_inform res;
	strcpy(res.id, id.c_str());
	strcpy(res.name, name.c_str());
	
	res.price = stod(price);
	res.add_price = stod(add_pirce);

	Time time;
	res.auction_time = time.string_to_time(str_time);

	strcpy(res.user_id, user_id.c_str());
	strcpy(res.description, description.c_str());

	res.st = OnSale;
	if (st == "Sold")
	{
		res.st = Sold;
	}
	else if (st == "OffShelf")
	{
		res.st = OffShelf;
	}
	return res;
}

static string info_to_string(commodity_inform info)
{
	string id = info.id;
	string name = info.name;
	string price = to_string(info.price);
	string add_price = to_string(info.add_price);
	Time time(info.auction_time);
	string str_time = time.time_to_string();
	string user_id = info.user_id;
	string description = info.description;
	string st = "OnSale";
	if (info.st == Sold)
	{
		st = "Sold";
	}
	else if (info.st == OffShelf)
	{
		st = "OffShelf";
	}
	string str_info = id + ',' + name + ',' + price + ',' + add_price + ',' + str_time + ',' + user_id + ',' + st + ',' + description;
	return str_info;
}

bool Commodity_list::Read_from_txt()
{
	char buffer[512];
	ifstream commofile("commodity.txt");
	if (!commofile.is_open())
	{
		return false;
	}

	while (!commofile.eof())
	{
		commofile.getline(buffer, 511);
		if (strlen(buffer) <= 1)
		{
			break;
		}

		string info(buffer);
		commodity_inform commo_info = string_to_info(info);
		if (head == NULL)
		{
			head = new commodity_list;
			head->data = commo_info;
			head->next = NULL;
			tail = head;
		}
		else
		{
			tail->next = new commodity_list;
			tail = tail->next;
			tail->data = commo_info;
			tail->next = NULL;
		}
	}
	return true;
}

void Commodity_list::Write_to_txt()
{
	ofstream userfile("commodity.txt");
	if (!userfile.is_open())
	{
		return;
	}
	else
	{
		commodity_list* commo_head = head;
		while (commo_head != NULL)
		{
			string info_str = info_to_string(commo_head->data);
			userfile << info_str + '\n';
			commo_head = commo_head->next;
		}
	}
}

void Commodity_list::Add_commodity(commodity_inform& info)
{
	if (tail == NULL)
	{
		string id = "M00001";
		strcpy(info.id, id.c_str());
		tail = new commodity_list;
		head = tail;
		head->next = NULL;
		head->data = info;
	}
	else
	{
		string last_id(tail->data.id, 1, 5);
		int num = stoi(last_id) + 1;
		string inum = to_string(num);
		while (inum.length() < 5)
		{
			inum = '0' + inum;
		}
		string id = "M" + inum;
		strcpy(info.id, id.c_str());
		tail->next = new commodity_list;
		tail = tail->next;
		tail->next = NULL;
		tail->data = info;
	}
	Write_to_txt();
}

commodity_list* Commodity_list::seller_check(char id[20])
{
	commodity_list* head = this->head;
	commodity_list* reshead = NULL;
	commodity_list* restail = NULL;
	string uid = id;
	while (head)
	{
		if (head->data.user_id == uid)
		{
			if (reshead == NULL)
			{
				reshead = new commodity_list;
				restail = reshead;
			}
			else
			{
				restail->next = new commodity_list;
				restail = restail->next;
			}
			restail->data = head->data;
			restail->next = NULL;
		}
		head = head->next;
	}
	return reshead;
}

commodity_list* Commodity_list::admin_check() 
{
	return this->head;
}

Commodity::Commodity(string name, double price, double add_pirce, string description, string uid)
{
	strcpy(this->info.name, name.c_str());
	strcpy(this->info.description, description.c_str());
	strcpy(this->info.user_id, uid.c_str());
	this->info.price = price;
	this->info.add_price = add_pirce;
}

void Commodity::Create_commodity()
{
	Time mytime;
	this->info.auction_time = mytime.current_time();
	this->info.st = OnSale;
	Commodity_list clist;
	clist.Read_from_txt();
	clist.Add_commodity(this->info);
}