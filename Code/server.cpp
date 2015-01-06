#include "server.h"

// It loads in Server the undelivered mailbox for all users
// ... provide by the users.txt file

void start(tServer &server, bool &error) {
	ifstream file;

	file.open(USERS_FILE.c_str());

	if (file.is_open()) 
	{
		loadUsers(server.list, file);
		error = false;
		file.close();
	}
	else {
		error = true;
	}
}

// It Save to users.txt file the undelivered mailbox (updated) for all users
 
void saveServer(const tServer &server) {
	ofstream file;

	file.open(USERS_FILE.c_str());
	saveUsers(server.list, file);

	file << "XXX" << endl;
	file.close();
}
