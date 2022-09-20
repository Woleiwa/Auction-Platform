#pragma once
#ifndef _COMMODITY_
#define _COMMODITY_
#include<cstring>
#include<iomanip>
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include"order.h"
using namespace std;
#include"mytime.h"
enum State { OnSale, Sold, OffShelf };

struct commodity_inform
{
	char id[10] = "\0";
	char name[50] = "\0";
	double price = 0;
	double add_price = 0;
	my_time auction_time;
	char user_id[10] = "\0";
	char description[200] = "\0";
	State st;
};

struct commodity_list
{
	commodity_inform data;
	commodity_list* next;
};

class Commodity_list
{
public:
	Commodity_list();

	~Commodity_list();

	bool Read_from_txt();

	void Write_to_txt();

	void Add_commodity(commodity_inform& info);

	commodity_inform admin_search_by_id(string id);

	commodity_inform consumer_search_by_id(string id);

	commodity_list* seller_check(char id[20]);

	commodity_list* admin_check();

	commodity_list* consumer_check(char id[20]);

	commodity_list* find_one_commodity(string cid);

	void freeze_user(string uid);
private:
	commodity_list* head = NULL, * tail = NULL;
};

class Commodity
{
private:
	commodity_inform info;
public:
	Commodity(string name, double price, double add_pirce, string description, string uid);

	Commodity(string id);

	void Create_commodity();

	commodity_inform my_info();

	void offshelf();
};
#endif // !_COMMODITY_



