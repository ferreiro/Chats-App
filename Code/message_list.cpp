#include "message_list.h"

// LoadmessageList function
// This Load a list from a file

void loadMessageList(tMessageList &list, ifstream &file) {
	int totalMessages;
	tMessage message;

	list.counter = 0;
	file >> totalMessages;

	if (totalMessages > 0) 
	{
		for (int i = 0; i < totalMessages; i++) 
		{
			loadMessage(message, file);	// Return the message from a file

			if (i < MAX_MESSAGES) {	
				list.messages[i] = message;
				list.counter++;	// Counter++: New message added
			}	
			else {
				// Skips the message and don't save it
			}
		}
	}
}

// saveMessageList function
// Saving a list to a determined file 

void saveMessageList(const tMessageList &list, ofstream &file) 
{
	file << list.counter << endl;
	for (int i = 0; i < list.counter; i++) {
		saveMessage(list.messages[i], file);
	}
}

// Last List Message
// Takes the last message of a List

void lastListMessage(const tMessageList &list, tMessage &message) {
	int lastPos;

	lastPos = list.counter - 1;
	message = list.messages[lastPos];
}

// InserMessage 
// This insert at the end of the function a message

void insertMessage(tMessageList &list, const tMessage &new_message) {
	if (list.counter < MAX_MESSAGES) {
		list.messages[list.counter] = new_message; // Save the message at the end of the array
		list.counter++; // Increase the counter: New element added to the array
	}
}