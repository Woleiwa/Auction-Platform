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
	char id[10];
	char name[50];
	double price;
	double add_price;
	my_time auction_time;
	char user_id[10];
	char description[200];
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

	commodity_inform admin_search_by_id(char id[20]);

	commodity_inform consume_search_by_id(char id[20]);

	commodity_list* seller_check(char id[20]);

	commodity_list* admin_check();

	commodity_list* comsume_check();
private:
	commodity_list* head = NULL, * tail = NULL;
};

class Commodity
{
private:
	commodity_inform info;
public:
	Commodity(string name, double price, double add_pirce, string description, string uid);

	Commodity(char id[20]);

	void Create_commodity();

	void Participate_in_auction();
};
#endif // !_COMMODITY_



