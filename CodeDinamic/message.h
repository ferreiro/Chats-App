#ifndef message_h
#define message_h

	#include <iostream>
	#include <string>
	using namespace std;
	#include <ctime>
	#include <sstream>
	#include <fstream>
	#include <iomanip>
	#include "color.h"

	const int PADDING = 5;
	const int CONSOLE_WIDTH = 70;
	
	typedef time_t tDate;

	typedef struct {
		string sender;
		tDate date;
		string text_message;
	} tMessage;

	typedef tMessage *tMessagePtr;

	void newMessage(tMessage &message, string sender, string text_message); // Return a single message
	void displayMessage(const tMessage &message, bool right); // Display one message
	void loadMessage(tMessage &message, ifstream &file); // Load messages from file
	void saveMessage(const tMessage &message, ofstream &file); // save messages from file
	string displayDate(tDate date); // Transform the string for humans
 
#endif