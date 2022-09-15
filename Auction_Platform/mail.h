#pragma once
#ifndef _MAIL_
#define _MAIL_

#include"mytime.h"
class Mail
{
private:
	char sender_id[10];
	char receiver_id[10];
	char massage[256];
	my_time time;
public:

};
#endif // !_MAIL_


