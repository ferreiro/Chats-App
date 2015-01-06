#ifndef chat_List
#define chat_List

	#include <iostream>
	#include <string>
	using namespace std;
	#include <fstream>

	#include "chat.h"
	#include "user_List.h"
	 
	typedef struct {
		tChatPtr items;
		int counter;
	} tChatList;
 
	int findChat(const tChatList &chatList, string username); // Return the position of the chat in the Client

	void eraseChats(tChatList &chats); // ERASE ALL CHATS


	void loadChats(tChatList &chats, string username, tUserList &userList); // LOAD ALL THE CHATS OF A USER:
	void saveChats(const tChatList &chats, string username); // SAVE all the chats of a user in his file
	void displayAllChats(const tChatList &chats); // Display all the chats in the home menu

	void createChat(tChatList &chats, tUserList &users, string sender); // Create a new chat
	void insertChat(tChatList &chats, const tChat &newChat);
	void openChat(tChatList &chats, int number, tUserList &userlist); // Opens and specific chat with an user
	void deleteChat(tChatList &chats, int number, string friendName, tUserList &users); // Delete an existing chat

	void sortByDate(tChatList &chats);
	void sortByName(tChatList &chats);

#endif

