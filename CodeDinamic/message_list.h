#ifndef messageList_h
#define messageList_h
	
	#include "message.h"

	typedef struct {
		tMessagePtr messages;  // Pointer... UNDELIVERIED MESSAGES!!!
		int counter;
	} tMessageList;

	void insertMessage(tMessageList &list, const tMessage &newMessage); // Add new message to the end of the list
	void loadMessageList(tMessageList &list, ifstream &file); // Loading list from a file
	void saveMessageList(const tMessageList &list, ofstream &file);
	void lastListMessage(const tMessageList &list, tMessage &message); // Takes the last message of a List
	
	void deleteMessageList(tMessageList &list); // Loading list from a file

#endif // !message_list