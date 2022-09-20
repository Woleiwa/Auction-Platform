#pragma once
#include "user.h"
#ifndef _CONSUMER_
#define _CONSUMER_
class Consumer: public User
{
public:
	using User::User;

	void operate();

	void check_order();

	void check_commodity();

	void Auction();

	void search_commodity();

	void get_information();

	void Auction(string id);
};

#endif