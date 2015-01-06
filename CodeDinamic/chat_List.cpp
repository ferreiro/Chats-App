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

// Insert Chat
// Insert Chat at the end of the list

void insertChat(tChatList &chats, const tChat &newChat)
{
	int currentCapacity, newCapacity;
	tChatList chatList;
	 
	currentCapacity = chats.counter;
	newCapacity = (currentCapacity * 3) / 2 + 1;

	chatList.counter = chats.counter;
	chatList.items = new tChat[newCapacity];

	for (int i = 0; i < chats.counter; i++) {
		chatList.items[i] = chats.items[i];
	}

	chatList.items[chatList.counter] = newChat;
	chatList.counter++;

	chats.counter = chatList.counter;
	chats.items = new tChat[newCapacity];

	chats = chatList;
}

// Loads all the chats of a user

void loadChats(tChatList &chats, string username, tUserList &userList) {
	bool ok;
	int position, currentCapacity, newCapacity, i;
	tChat chat;
	ifstream file;
	string filename;

	filename = username + "_chats.txt";
	file.open(filename);

	if (file.is_open()) 
	{
		i = 0;
		ok = true;
		chats.counter = 0;

		file >> currentCapacity;
		newCapacity = (currentCapacity * 3) / 2 + 1;

		chats.items = new tChat[newCapacity]; // Create a Dinamic Array in the heap of tChat
		
		while (i < currentCapacity) 
		{
			loadChat(file, username, chat);
			position = findUser(userList, chat.myfriend); // Is the username in our Database?

			if (position != -1)
			{
				chats.items[chats.counter] = chat;	// Save the chat into the array
				chats.counter++;
			}
			i++;
		}
		file.close();
	} 
	else {
		chats.counter = 0;
	}
}

// Erase Chats
void eraseChats(tChatList &chats) 
{
	delete[] chats.items;
	chats.counter = 0;
}

// Save All Chats
// Save all the chats of a user

void saveChats(const tChatList &chats, string username) {
	ofstream file;
	string filename;

	filename = username + "_chats.txt";
	file.open(filename);

	file << chats.counter << endl; // Print the number of Total Chats

	for (int i = 0; i < chats.counter; i++) {
		saveChat(chats.items[i], file);
	}
	file.close(); 

}

// Open Chat
// Open a specific chat with my friend

void openChat(tChatList &chats, int number, tUserList &userlist) {
	int friendIndex;
	int i = 0;
	bool end = false;

	while ((i < chats.counter) && (!end)) {

		if (i == number) {
			
			friendIndex = findUser(userlist, chats.items[i].myfriend);
			openSingleChat(chats.items[i], userlist.users[friendIndex]->list); 
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
	bool validUser, isNewChat;
	string recipient, txtMsg;

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

	if (!validUser) 
	{ 
		setColor(light_red);
		if (recipient == sender) {
			cout << endl << setw(PADDING) << left << " " << "Maybe this website will help you..." << endl;
			cout << setw(PADDING) << left << " " << "www.BuyFriends.com" << endl;
			Sleep(3500);
		}
		else {
			cout << setw(PADDING) << left << " " << "The username doesn't Exist!" << endl;
			Sleep(1000);
		}		
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
		insertMessage(users.users[index]->list, message); // Sent the message to my friend

		newChat(chat, message, recipient);
		insertChat(chats, chat); // Inser the chat on my List
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
				insertMessage(users.users[serverPosition]->list, message);
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
	tChat auxList;
	
	int jLastMsg, iLastMsg;
	int jDate, iDate;

	//-------------- Sorting Method ------------------
	for (int i = 0; i < chats.counter - 1; i++) {
		// From first to one before the last...
		for (int j = i + 1; j < chats.counter; j++) {

			jLastMsg = chats.items[j].messages.counter - 1;
			jDate = chats.items[j].messages.messages[jLastMsg].date;

			iLastMsg = chats.items[i].messages.counter - 1;
			iDate = chats.items[i].messages.messages[iLastMsg].date;
			
			// From i + 1 to end
			if (jDate < iDate) {
				auxList = chats.items[i];
				chats.items[i] = chats.items[j];
				chats.items[j] = auxList;
			}
		}
	}
	//------------------------------------------------------

}

