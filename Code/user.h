#ifndef user_h
#define user_h

	#include <string>
	#include <iostream>
	using namespace std;
	#include <fstream>
	#include "message_list.h"

	typedef struct {
		string username;
		tMessageList list; // undelivered message mailbox
	} tUser;

	void loadUser(tUser &user, ifstream &file, bool &sentinel);
	void saveUser(const tUser &user, ofstream &file);
 
#endif
