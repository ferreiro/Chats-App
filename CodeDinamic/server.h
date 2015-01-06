#ifndef server_h
#define server_h

	#include "user_List.h"

	const string USERS_FILE = "users.txt";

	typedef struct {
		tUserList list;
	} tServer;


	void start(tServer &server, bool &error); // Start the server at the beginning
	void saveServer(const tServer &server);

	bool undeliveredMessage(tServer &server);


#endif