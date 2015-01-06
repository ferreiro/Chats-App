#ifndef client_h
#define client_h

#include "chat_List.h"
#include "user_List.h"
#include "server.h"
#include <fstream>

const int MENU_PADDING = 35;
const int SLEEP_TIME = 500;

typedef struct {
	string username;
	tChatList mychats;
} tClient;

typedef enum{
	open, erase, sortDate, sortName, create, quit, error
} tCommand;

// Return chats of the username

void startTheClient(tClient &client, string username, tServer &server);
void saveClient(const tClient &client);
void runClient(tClient &client, tUserList &userlist);
void menu(tCommand &command, int &number);



#endif