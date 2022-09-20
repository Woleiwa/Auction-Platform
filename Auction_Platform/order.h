#pragma once
#ifndef _ORDER_
#define _ORDER_
#include<cstring>
#include<iomanip>
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<conio.h>
#include"mytime.h"
enum order_state{Deal, Cancel, Waiting};
struct order
{
	char order_id[20];
	char seller_id[20];
	char auctioneer[20];
	char commodity_id[20];
	char commodity_name[20];
	my_time time;
	double bid;
	order_state st;
};

struct order_list
{
	order data;
	order_list* next;
};

class Order_List
{
private:
	order_list* head = NULL, * tail = NULL;
public:
	bool Read_from_txt();

	void Write_to_txt();

	void Add_to_list(order& info);

	order_list* admin_check();

	order_list* consumer_check(string uid);

	order_list* seller_check(string uid);
	
	double max_price(string commodity_id);

	void OffShelf(string cid);

	void freeze_user(string id);
};

class Order
{
private:
	order info;
public:
	Order(string seller_id, string auctioneer_id, string commodity_id, string commodity_name, double bid);
	
	Order(order info);

	order my_info(order info);

	void add_to_olist();
};

#endif // !_ORDER_



