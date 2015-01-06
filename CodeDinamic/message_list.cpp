#include "message_list.h"

// LoadmessageList function
// This Load a list from a file

void loadMessageList(tMessageList &list, ifstream &file) {
	int totalMessages, newCapacity, pos;
	tMessage message;
	
	file >> totalMessages;
	newCapacity = (totalMessages * 3) / 2 + 1;

	list.counter = 0;
	list.messages = new tMessage[newCapacity];

	if (totalMessages > 0) 
	{
		for (int i = 0; i < totalMessages; i++) 
		{
			loadMessage(message, file);	// Return the message from a file
			list.messages[i] = message;
			list.counter++;	// Counter++: New message added
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

void insertMessage(tMessageList &list, const tMessage &newMessage)  
{
	int currentCapacity, newCapacity;
	tMessageList messageList;

	currentCapacity = list.counter;
	newCapacity = (currentCapacity * 3) / 2 + 1;

	messageList.counter = list.counter;
	messageList.messages = new tMessage[newCapacity];

	for (int i = 0; i < list.counter; i++) {
		messageList.messages[i] = list.messages[i];
	}

	messageList.messages[messageList.counter] = newMessage;
	messageList.counter++;

	list.counter = messageList.counter;
	list.messages = new tMessage[newCapacity];

	list = messageList;
}

// Delete message list 
// Erasing the data from the heap...

void deleteMessageList(tMessageList &list) {
	delete[] list.messages;
	list.counter = 0;
}