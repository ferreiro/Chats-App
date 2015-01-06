#ifndef messageList_h
#define messageList_h
	
	#include "message.h"
 
	const int MAX_MESSAGES = 10;
	 
	typedef struct {
		tMessage messages[MAX_MESSAGES];	// UNDELIVERIED MESSAGES!!!
		int counter;
	} tMessageList;

	void insertMessage(tMessageList &list, const tMessage &new_message); // Add new message to the end of the list
	void loadMessageList(tMessageList &list, ifstream &file); // Loading list from a file
	void saveMessageList(const tMessageList &list, ofstream &file);
	void lastListMessage(const tMessageList &list, tMessage &message); // Takes the last message of a List

#endif // !message_list