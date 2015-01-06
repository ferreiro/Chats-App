#include "client_ok.h"


// Start Client will save the chat list of a given username
void startTheClient(tClient &client, string username, tServer &server) {
	// F10
	client.username = username;
	loadChats(client.mychats, username, server.list);
}

void saveClient(const tClient &client) {
	// Press F10 to see what happens
	saveChats(client.mychats, client.username);
}

void runClient(tClient &client, tUserList &userlist) {
	int number;
	string recipient, friendName;
	tCommand command;

	command = create; // Garbage

	while (command != quit) {

		Sleep(SLEEP_TIME);
		system("cls");

		cout << endl << setw(PADDING) << " " << "Welcome to Chatsapp " << client.username << endl;
		printLines();
		cout << endl;
		displayAllChats(client.mychats); // F11
		menu(command, number);

		if ((command != quit) && command != error) {

			if (command == create) 
			{
				createChat(client.mychats, userlist, client.username);
			}
			else if (command == erase) 
			{
				if ((number < 0) || (number >= client.mychats.counter)) {
					setColor(light_red);
					cout << endl << setw(PADDING) << " " << "There are any created chat with this index!";
					setColor(white);
				}
				else {
					deleteChat(client.mychats, number, client.mychats.items[number].myfriend, userlist);
				}
			}
			else if (command == open) 
			{
				if ((number < 0) || (number >= client.mychats.counter)) {
					setColor(light_red);
					cout << endl << setw(PADDING) << " " << "There are any created chat with this index!";
					setColor(white);
				}
				else {
					openChat(client.mychats, number, userlist);
				}				
			}
			else if (command == sortDate) {
				sortByDate(client.mychats);
			}
			else if (command == sortName) {
				sortByName(client.mychats);
			}
		}

		if (command == error) {
			setColor(light_red);
			cout << endl << setw(PADDING) << " " << "Insert a valid option";
			setColor(white);
		}
	}


}

void menu(tCommand &command, int &number) {
	string input;
	char firstChar, secondChar;

	printLines();
	cout << endl;

	cout << setw(PADDING) << left << " " << setw(MENU_PADDING) << left << "Open Chat N: c N <enter>";
	cout << setw(MENU_PADDING) << right << "Create new chat: n <enter>" << setw(PADDING) << right << " ";

	cout << setw(PADDING) << left << " " << setw(MENU_PADDING) << left << "Delete Chat N: e N <enter";
	cout << setw(MENU_PADDING) << right << "Short chat by name: o n <enter>" << setw(PADDING) << right << " ";

	cout << setw(PADDING) << left << " " << setw(MENU_PADDING) << left << "Short chats by date: o f <enter>";
	cout << setw(MENU_PADDING) << right << "Quit: s <enter>" << setw(PADDING) << right << " ";
	 
	printLines();

	cout << endl << setw(PADDING) << left << " ";
	cin >> firstChar;

	if (firstChar == 's') {
		command = quit; // Exist the program
	}
	else if (firstChar == 'n') {
		command = create; // Create New Chat
	}
	else {

		if ((firstChar == 'c') || (firstChar == 'e')) {

			cin >> number;

			if (firstChar == 'c') {
				command = open;
			}
			else if (firstChar == 'e') {
				command = erase;
			}
		}
		else if((firstChar == 'o')) {

			cin >> secondChar;

			if (secondChar == 'f') {
				command = sortDate;
			}
			else if (secondChar == 'n') {
				command = sortName;
			}
			else {
				command = error; // Invalid letter 
			}
		}
		else {
			// No es ninguna de las opciones anteriores... Error!
			command = error;
		}
	}

}
