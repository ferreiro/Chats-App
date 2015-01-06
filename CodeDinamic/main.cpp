/*
  _____ _           _                                      __ 
 / ____| |         | |         /\                         /_ |
| |    | |__   __ _| |_ ___   /  \   _ __  _ __   __   __  | |
| |    | '_ \ / _` | __/ __| / /\ \ | '_ \| '_ \  \ \ / /  | |
| |____| | | | (_| | |_\__ \/ ____ \| |_) | |_) |  \ V /   | |
 \_____|_| |_|\__,_|\__|___/_/    \_\ .__/| .__/    \_/    |_|. 
                                    | |   | |                 
       Jorge García Ferreiro        |_|   |_|                 
       1ºI. English Course.
*/

#include <iostream>
#include <string>
using namespace std;
#include <ctime>
#include <fstream>
#include <iomanip>
#include <Windows.h>

#include "server.h"
#include "client.h"
 
const int SLEEP = 500; 

void printLogo();
void printLogo2();
void generateLogo();
void updatePending(tServer &server, tClient &client);

int main() {
	int index = 0;
	bool error;
	string username;
	tServer server;
	tClient client;
	
	start(server, error);

	if (error) {
		cout << "We coudln't load the users and messages";
	} 
	else {

		do {
			Sleep(SLEEP);
			system("cls");

			generateLogo();
			cout << endl << "You can access to this users: Lorena, dcosta, pepe, susana and simeone" << endl;
			cout << "Al you need is modify the files in order to add / delete users";
			cout << endl << endl << "User <0 to quit>: ";
			cin >> username;

			if (username != "0") {

				index = findUser(server.list, username); // Looking if the user exist in the Array. Return -1 if not

				if (index != -1) 
				{
					startTheClient(client, username, server);// F10!!!!
					updatePending(server, client); // F11!!!
					runClient(client, server.list);
					saveClient(client);
					eraseChats(client.mychats);
				}
				else {
					cout << "Sorry. The username doesn't exist";
				}
			}

		} while (username != "0");
		saveServer(server); // Save the server
		eraseUserList(server.list);
	}
	return 0;
}

// Update server undelivered messages of a specific user

void updatePending(tServer &server, tClient &client) {
	int i;
	bool stop;
	tChat newChat;
	tMessage message;
	string sender;
	int userPosition, position, totalMsg, chatPosition;

	position = findUser(server.list, client.username); // Position of the current user in the array

	if (position != -1) 
	{
		totalMsg = server.list.users[position]->list.counter;

		while (totalMsg > 0) 
		{
			message = server.list.users[position]->list.messages[0]; // First Message 
			stop = false;
			i = 0;

			if (totalMsg != 1) {
				for (int i = 0; i < totalMsg; i++) {
					server.list.users[position]->list.messages[i] = server.list.users[position]->list.messages[i + 1];
				}
			} 

			server.list.users[position]->list.counter--; // Decrease the undeliver message
			totalMsg = server.list.users[position]->list.counter; // Update total messages
			sender = message.sender;

			userPosition = findUser(server.list, sender); // Is the username in our Database? -1 if is not in the database
			 
			if (userPosition != -1) 
			{
				chatPosition = findChat(client.mychats, sender);  // Search if the chat with that user exists 

				if (chatPosition == -1)
				{
					// -1 = The chat is new

					newChat.myfriend = message.sender;
					newChat.owner = client.username;
					newChat.messages.messages = new tMessage[10];
					newChat.messages.counter = 1;
					newChat.messages.messages[0] = message;
					insertChat(client.mychats, newChat);
				}
				else
				{
					// Existing chat
					insertMessage(client.mychats.items[chatPosition].messages, message);
				}
			}			
		}		
	}
}
  
void printLogo() {

	cout << "  ,ad8888ba,   88        88         db    888888888888  ad88888ba   " << endl;
	cout << " d8'      `8b  88        88        d88b        88      d8       8b  " << endl;
	cout << "d8'            88        88       d8'`8b       88      Y8,          " << endl;
	cout << "88             88aaaaaaaa88      d8'  `8b      88      `Y8aaaaa,    " << endl;
	cout << "88             888888888888     d8YaaaaY8b     88        `aaaaaaab " << endl;
	cout << "Y8,            88        88    d8aaaaaaaa8b    88              `8b  " << endl;
	cout << " Y8a.    .a8P  88        88   d8'        `8b   88      Y8a     a8P  " << endl;
	cout << "  `Y8888Y'     88        88  d8'          `8b  88        Y88888P    " << endl;
}

void printLogo2() {

	cout << "       db         88888888ba   88888888ba   " << endl;
	cout << "      d88b        88       8b  88       8b  " << endl;
	cout << "     d8'`8b       88      ,8P  88      ,8P  " << endl;
	cout << "    d8'  `8b      88aaaaaa8P'  88aaaaaa8P'  " << endl;
	cout << "   d8YaaaaY8b     88           88           " << endl;
	cout << "  d8888888888b    88           88           " << endl;
	cout << " d8'        `8b   88           88           " << endl;
	cout << "d8'          `8b  88           88           " << endl;
}

void generateLogo() {
	int random = 0;

	for (int i = 0; i < 3; i++) 
	{
		Sleep(1);
		system("cls"); 

		if (i == 0) {
			setColor(light_gray);
		}

		else if (i == 1) {
			setColor(dark_yellow);
		}

		else if (i == 2) {
			setColor(light_yellow);
		}

		printLogo();
		printLogo2();
	}
	setColor(white);
}

