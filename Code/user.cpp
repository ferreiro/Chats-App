#include "user.h"

void loadUser(tUser &user, ifstream &file, bool &sentinel) {
	string username;
	sentinel = false;

	file >> username;

	if (username != "XXX") {
		user.username = username;
		loadMessageList(user.list, file);	// Call to loadList on message_list.cpp
	}
	else {
		sentinel = true;	// We have the sentinel
	}
}

void saveUser(const tUser &user, ofstream &file)  {

	file << user.username << endl;
	saveMessageList(user.list, file);	// Call to savelist on message_list.cpp

}

