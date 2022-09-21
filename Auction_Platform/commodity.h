#pragma once
#ifndef _COMMODITY_
#define _COMMODITY_

#include<string>
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

struct commodity_relevant
{
	commodity_inform data;
	double relevance = 0;
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



