#ifndef userList_h
#define userList_h

	#include "user.h"

	const int MAX_USERS = 50;
	 
	typedef tUserPtr tUsersArray[MAX_USERS];

	typedef struct {
		tUsersArray users;
		int counter;
	} tUserList;

	void loadUsers(tUserList &users, ifstream &file); // Loading the User list
	void saveUsers(const tUserList &userList, ofstream &file); // Saving the User list
	void eraseUserList(tUserList &users);

	void insertUser(tUserList &list, const tUser &user); // Insert a user at the end
	int  findUser(const tUserList &list, string username); // Return the position of the user in the list


#endif
