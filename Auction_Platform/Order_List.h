#pragma once
#include"order.h"
#ifndef _ORDERLIST_
#define _ORDERLIST_
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

	bool update(string commodity_id);
};
#endif // !_ORDERLIST_



