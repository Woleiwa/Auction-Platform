#pragma once



#ifndef _ADMIN_
#define _ADMIN_
class Admin
{
private:
	const char user_id[20] = "Admin";
	const char password[20] = "123456";
public:
	Admin();

	void admin_operate();

	void check_user();

	void check_commodity();

	void check_order();

	void check_mail();
};
#endif // !_ADMIN_



