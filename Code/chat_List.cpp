#include "chat_List.h"


// Find Chat function
// Return the position of the chat in the Client

int findChat(const tChatList &chatList, string username) {
	int position = -1;
	int i = 0;
	bool isNewChat = true;

	while ((i < chatList.counter) && (isNewChat)) {

		if (chatList.items[i].myfriend == username) {
			isNewChat = false;
			position = i; // CHAT POSITION
		}
		i++;
	}

	return position; // -1 if the user doesn't exist
}

// Inser Chat
// Insert Chat at the end of the list

void insertChat(tChatList &chats, const tChat &chat)
{
	if (chats.counter < MAX_CHATS) {
		chats.items[chats.counter] = chat;	// Save the chat into the array
		chats.counter++;
	}
}

// Loads all the chats of a user

void loadChats(tChatList &chats, string username, tUserList &userList) {
	bool ok;
	int position;
	tChat chat;
	ifstream file;
	string filename;

	filename = username + "_chats.txt";
	file.open(filename);

	if (file.is_open()) 
	{
		ok = true;
		chats.counter = 0;

		while ((chats.counter < MAX_CHATS) && (ok)) {

			loadChat(file, username, chat, ok);
			position = findUser(userList, chat.myfriend);

			if ((ok) && (position != -1)) 
			{
				chats.items[chats.counter] = chat;	// Save the chat into the array
				chats.counter++;
			}
		}
		file.close();
	} 
}


// Save All Chats
// Save all the chats of a user

void saveChats(const tChatList &chats, string username) {
	ofstream file;
	string filename;

	filename = username + "_chats.txt";
	file.open(filename);
	 
	for (int i = 0; i < chats.counter; i++) {
		saveChat(chats.items[i], file);
	}
	file << "XXX" << endl; 
	file.close(); 

}

// Open Chat
// Open a specific chat with my friend

void openChat(tChatList &chats, int number, tUserList &userlist) {
	tMessageList friendMessageList;
	int friendIndex;
	int i = 0;
	bool end = false;

	while ((i < chats.counter) && (!end)) {

		if (i == number) {
			
			friendIndex = findUser(userlist, chats.items[i].myfriend);
			openSingleChat(chats.items[i], userlist.users[friendIndex].list); 
			end = true;

		}
		else {
			i++;
		}
	}
}

// Create Chat
// Open a specific chat with my friend

void createChat(tChatList &chats, tUserList &users, string sender) {
	tChat chat;
	tMessage message;
	int index, chatPosition;
	bool validUser, isNewChat, avaliableSpace;
	string recipient, txtMsg;

	if (chats.counter < MAX_CHATS) {

		cout << endl << setw(PADDING) << left << " " << "Plese indicates the recipient name: ";
		setColor(light_yellow);
		cin >> recipient;
		setColor(white);


		if (recipient == sender) {
			validUser = false; // You can't create a chat with yourself!!
		}
		else 
		{
			index = findUser(users, recipient); // Looking if the user exist in the Array. Return -1 if not
			
			if (index != -1) {
				validUser = true; // The user exists
			}
			else {
				validUser = false; // Invalid user
			}
		}
				
		if (validUser)
		{
			chatPosition = findChat(chats, recipient);

			if (chatPosition != -1) {
				isNewChat = false;
			}
			else {
				isNewChat = true;
			}
		}

		// After all. What the program must do? Create a chat or not?

		if (!validUser) { 
			setColor(light_red);
			cout << setw(PADDING) << left << " " << "The username doesn't Exist or you can't chat with yourself!" << endl;
			Sleep(1000);
			setColor(white);
		}
		else if (!isNewChat) {
			setColor(light_red);
			cout << setw(PADDING) << left << " " << "You've a chat with " << recipient << endl;
			Sleep(800);
			setColor(white);
		}
		else if ((validUser) && (isNewChat))
		{
			txtMsg = "New chat initiated by " + sender;
			newMessage(message, sender, txtMsg);
			insertMessage(users.users[index].list, message); // Sent he message to my friend

			newChat(chat, message, recipient);
			insertChat(chats, chat); // Inser the chat on my List
		}
	}
	else {
		setColor(light_red);
		cout << setw(PADDING) << left << " " << "You can't create one more Chat. Memory Full" << endl;
		cout << setw(PADDING) << left << " " << "Maximun of Chats: " << MAX_CHATS << endl;
		Sleep(2000);
		setColor(white);
	}
}

// Create Chat
// Open a specific chat with my friend

void deleteChat(tChatList &chats, int number, string friendName, tUserList &users) {
	int position, serverPosition;
	bool validChat;	
	tChat chat;
	tMessage message;	
	string answer, txtMsg, owner;
	
	cout << setw(PADDING) << left << " " << "Do you really want to delete this chat? [yes/no]: ";
	setColor(light_yellow);
	cin >> answer;
	setColor(white);
	 
	if (answer == "yes") {

		position = findChat(chats, friendName); // Buscar si el chat existe en mi cliente (Return -1 si no existe)

		if (position != -1) {
			validChat = true; // The Chat exist
		}
		else {
			validChat = false;
		}

		if (validChat) {

			owner = chats.items[number].owner;

			for (int i = number; i < chats.counter; i++) {
				if (i < chats.counter - 1) {
					chats.items[i] = chats.items[i + 1]; // Delete the chat
				}
			}

			chats.counter--; // Decrease the array elements

			txtMsg = "Chat closed by " + owner;
			newMessage(message, owner, txtMsg);

			serverPosition = findUser(users, friendName);

			if (serverPosition != -1) {
				insertMessage(users.users[serverPosition].list, message);
			}

			setColor(light_green);
			cout << setw(PADDING) << left << " " << "You erase the chat" << endl;
			Sleep(800);
			setColor(white);
		}
		else {
			setColor(light_green);
			cout << setw(PADDING) << left << " " << "This chat doesn't exist" << endl;
			Sleep(800);
			setColor(white);
		}
	}
	else if (answer == "no") 
	{
		setColor(light_green);
		cout << setw(PADDING) << left << " " << "You don't erase the chat" << endl;
		Sleep(800);
		setColor(white);
	}
	else {
		setColor(light_red);
		cout << setw(PADDING) << left << " " << "Invalid option" << endl;
		Sleep(800);
		setColor(white);
	}	
}

// Display All Chats
// Display the list of chats

void displayAllChats(const tChatList &chats) {

	if (chats.counter == 0) {
		setColor(light_gray);
		cout << setw(PADDING) << left << " " << "NO CHATS AVALIABLE!!" << endl;
		setColor(white);
		printLines();
	}
	else 
	{
		for (int i = 0; i < chats.counter; i++) {
			displaySummary(chats.items[i], i); // Show the last message of a Chat.
		}
	}

}

// Sort By Name
// Order using swap!

void sortByName(tChatList &chats) {
	tChat tmpChat;
	string tmp;
	int pos;

	// From second element to last one...
	for (int i = 1; i < chats.counter; i++) {
		pos = i;
		while ((pos > 0) && (chats.items[pos - 1].myfriend > chats.items[pos].myfriend)) {
			// Swap
			tmpChat = chats.items[pos];
			chats.items[pos] = chats.items[pos - 1];
			chats.items[pos - 1] = tmpChat;
			pos--;
		}
	}
}

// Sort By Date
// Order using swap!
 

void sortByDate(tChatList &chats) {

	//-------------- Sorting Method -----------------------------
	bool swap = true;
	int i = 0;
	while ((i < chats.counter) && swap) {
		// From 1st to second to last if there are swaps...
		swap = false;
		for (int j = chats.counter - 1; j > i; j--) {
			int lastMsg = chats.items[j].messages.counter;
			// From last to i + 1...
			if (chats.items[j].messages.messages[lastMsg].date < chats.items[j - 1].messages.messages[lastMsg].date) {
				tChat tmp;
				tmp = chats.items[j];
				chats.items[j] = chats.items[j - 1];
				chats.items[j - 1] = tmp;
				swap = true;
			}
		}
		if (swap) {
			i++;
		}
	}

}
/*
void sortByDate(tChatList &chats) {
	tMessage preMessage, message;
	tChat tmp;
	int pos;

	// From second element to last one...
	for (int i = 1; i < chats.counter; i++) {
		pos = i; 

		lastListMessage(chats.items[i - 1].messages, preMessage);
		lastListMessage(chats.items[i].messages, message);
 
		// While not at the beginning and previous higher...
		while ((pos > 0) && (preMessage.date > message.date)) {

			// Swap...
			tmp = chats.items[pos];
			chats.items[pos] = chats.items[pos - 1];
			chats.items[pos - 1] = tmp;
			pos--; 
		}
	}
}
*/