#include "chat.h"
 
// NewChat
// Return a tChat variable

void newChat(tChat &chat, tMessage message, string recipient) 
{
	chat.owner = message.sender;
	chat.myfriend = recipient;
	chat.messages.messages = new tMessage[10];
	chat.messages.counter = 1;
	chat.messages.messages[0] = message;
}


// LoadChat
// Load a chat with another user

void loadChat(ifstream &file, string username, tChat &chat) {
	string auxName;

	file >> auxName;
	 
	chat.owner = username;
	chat.myfriend = auxName;

	loadMessageList(chat.messages, file);	// Load the list of messages with his friend
 
}

// SaveChat
// Save a chat with another user in a file

void saveChat(const tChat &chat, ofstream &file) {

	file << chat.myfriend << endl;
	file << chat.messages.counter << endl;

	for (int msgID = 0; msgID < chat.messages.counter; msgID++) {
		file << chat.messages.messages[msgID].sender << " ";
		file << chat.messages.messages[msgID].date << " ";
		file << chat.messages.messages[msgID].text_message << endl;
	}
}

// It will display all messages in chat and accept new messages
// New messages are added to the chat and to newMsg

void openSingleChat(tChat &chat, tMessageList &messageList) {
	tMessage message;
	string inputMessage;
	
	do {
		Sleep(500);
		system("cls");
		displayChat(chat);

		cout << endl << setw(PADDING) << " " << chat.owner << ", write your message <$quit$ to exist>: ";
		cin.sync();
		getline(cin, inputMessage);
		 
		if (inputMessage == "$quit$") 
		{
			// Closed the chat
			setColor(light_green);
			cout << endl << setw(PADDING) << left << " " << "OK! You closed the chat. " << endl;
			Sleep(600);
			setColor(white);
		}
		else 
		{
			// Insert a Message
			newMessage(message, chat.owner, inputMessage); // Create a new message
			insertMessage(chat.messages, message); // Insert at the end of the user chatList
			insertMessage(messageList, message); // insertar en la bandeja del destinatario
		}

	} while(inputMessage != "$quit$"); 
}

// Display Summary
// Show the recent messages from a single chat

void displaySummary(const tChat &chat, int n) {
	bool align_right;
	int lastPosition;
	tMessage lastMsg;

	setColor(light_yellow);
	cout << setw(PADDING) << " " << n << ": " << chat.myfriend << endl; // Message number in the home screen
	setColor(white);

	if (chat.messages.counter > 0) {
		lastPosition = chat.messages.counter - 1;
		lastMsg = chat.messages.messages[lastPosition];
		align_right = false;
		displayMessage(lastMsg, align_right);
	}
	else {
		cout << "0 messages with dat user";
	}	
	cout << endl;
}


// Display the chat
// Display all the messages from a conversation with two users

void displayChat(const tChat &chat) {
	bool align_right;

	cout << endl << setw(PADDING) << " " << "You're chatting with ";
	setColor(light_yellow); 
	cout << chat.myfriend << endl; // My friend Name
	setColor(white);
	printLines();

	for (int i = 0; i < chat.messages.counter; i++) {

		if (chat.messages.messages[i].sender == chat.myfriend) {
			// Other user messages
			align_right = false;
			displayMessage(chat.messages.messages[i], align_right);
		}
		else {
			// My message
			align_right = true;
			displayMessage(chat.messages.messages[i], align_right);
		}
		printLines();
	}
}


// Print lines
// Auxiliary Function to print lines in the screen

void printLines() 
{
	for (int i = 0; i < LINES_WITDH; i++) {
		cout << "_";
	}
} 