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

	void sellar_operate();

	void add_commodity();

	void check_my_commodity();

	void check_my_order();

	void exit();
};

#endif
