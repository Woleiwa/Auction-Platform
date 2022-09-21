#include"commodity.h"
#include"order.h"
#include<cstring>
#include<iomanip>
#include<iostream>
#include<fstream>
#include<mutex>
#include<cstdlib>
#include"Commodity_List.h"
#include"Order_List.h"
extern Order_List olist;
extern Commodity_List clist;
extern mutex c_mtx;

Commodity::Commodity(string name, double price, double add_pirce, string description, string uid)
{
	strcpy(this->info.name, name.c_str());
	strcpy(this->info.description, description.c_str());
	strcpy(this->info.user_id, uid.c_str());
	this->info.price = price;
	this->info.add_price = add_pirce;
}

Commodity::Commodity(string id)
{
	Commodity_List c_list;
	c_list.Read_from_txt();
	commodity_inform info = c_list.admin_search_by_id(id);
	this->info = info;
}

commodity_inform Commodity::my_info()
{
	return this->info;
}

void Commodity::Create_commodity()
{
	Time mytime;
	this->info.auction_time = mytime.current_time();
	this->info.st = OnSale;
	clist.Read_from_txt();
	clist.Add_commodity(this->info);
}

void Commodity::offshelf()
{
	this->info.st = OffShelf;
	clist.Read_from_txt();
	string cid = this->info.id;
	commodity_list* pointer = clist.find_one_commodity(cid);
	pointer->data.st = OffShelf;
	clist.Write_to_txt();
	olist.Read_from_txt();
	olist.OffShelf(cid);
	olist.Write_to_txt();
}

