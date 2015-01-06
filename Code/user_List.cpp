#include <iostream>
#include <string>
using namespace std;
#include "user_List.h"

// findUser function : Return the position of the user in the list

int findUser(const tUserList &list, string username) {
	bool found;
	int i, position = -1;
 
	i = 0;
	found = false;

	while ((i < list.counter) && (!found)) {
		if (list.users[i].username == username) {
			position = i;
			found = true;
		}
		else {
			i++;
		}
	}

	return position; // -1 if the user doesn't exist
}

// Load Users function: Load all the users from a file.

void loadUsers(tUserList &users, ifstream &file) {
	tUser auxUser;
	bool sentinel;
	int position;
	
	sentinel = false;
	users.counter = 0;	// 0 users in the list

	while (!sentinel) 
	{
		loadUser(auxUser, file, sentinel);	// Pass the username + undelivered inbox
		
		if ((!sentinel) && (users.counter < MAX_USERS)) 
		{
			users.users[users.counter] = auxUser;
			users.counter++; // If not sentinel, we have one more user
		}
	}
}

void saveUsers(const tUserList &userList, ofstream &file) {

	for (int i = 0; i < userList.counter; i++) {
		saveUser(userList.users[i], file);
	}
}