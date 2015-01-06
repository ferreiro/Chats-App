#ifndef chat_h
#define chat_h
	
	#include <iostream>
	#include <string>
	using namespace std;
	#include "message_list.h"

	const int LINES_WITDH = 80;
 
	typedef struct {
		string owner;
		string myfriend;
		tMessageList messages;
	} tChat;
	 
	typedef tChat *tChatPtr;

	void printLines();
 
	void loadChat(ifstream &file, string username, tChat &chat); // Load a chat with another user
	void saveChat(const tChat &chat, ofstream &file); // Save a chat with another user in a file
	void newChat(tChat &chat, tMessage message, string recipient); // Return a tChat variable

	void openSingleChat(tChat &chat, tMessageList &messageList); // It will display all messages in chat and accept new messages
	void displayChat(const tChat &chat); // Display all the messages from a conversation with two users
	void displaySummary(const tChat &chat, int n); // Show the recent messages from a single chat

#endif

