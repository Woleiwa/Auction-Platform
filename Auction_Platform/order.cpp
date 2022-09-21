#include"order.h"
#include"commodity.h"
#include"user.h"
#include<mutex>
#include"Order_List.h"
#include"User_List.h"
extern Order_List olist;
extern User_List ulist;
extern mutex o_mtx;

Order::Order(string seller_id, string auctioneer_id, string commodity_id, string commodity_name, double bid)
{
	strcpy(this->info.seller_id, seller_id.c_str());
	strcpy(this->info.auctioneer, auctioneer_id.c_str());
	strcpy(this->info.commodity_id, commodity_id.c_str());
	strcpy(this->info.commodity_name, commodity_name.c_str());
	this->info.bid = bid;
	Time time;
	this->info.time = time.current_time();
	this->info.st = Waiting;
}

Order::Order(order info)
{
	this->info = info;
}

order Order::my_info(order info)
{
	return this->info;
}

void Order::add_to_olist()
{
	olist.Read_from_txt();
	olist.Add_to_list(this->info);
	olist.Write_to_txt();
}

