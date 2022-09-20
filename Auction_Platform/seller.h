#pragma once
#include "user.h"
#ifndef _SELLER_
#define _SELLER_


class Seller: public User
{
private:

public:
	using User::User;

	~Seller();

	void operate();

	void add_commodity();

	void check_commodity();

	void check_order();

	void change_commo_information();

	void off_shelf();
};

#endif
