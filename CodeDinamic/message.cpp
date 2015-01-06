#include "message.h" 

// New Message
// Return a variable of tMessage.

void newMessage(tMessage &message, string sender, string text_message) {
	message.sender = sender;
	message.date = time(0);
	message.text_message = text_message;
}

// Display Message
// Display a single message in the screen

void displayMessage(const tMessage &message, bool align_right) {
	string the_date;
	string data_info, line;

	the_date = message.date;
	the_date = displayDate(message.date);

	data_info = message.sender + " <" + the_date + ">";
	setColor(light_gray); // Set the window color

	if (align_right) {
		cout << setw(CONSOLE_WIDTH) << right << data_info << setw(PADDING) << " " << endl; // Message
		setColor(white);
		cout << setw(CONSOLE_WIDTH) << right << message.text_message << setw(PADDING) << " " << endl; // Message
	}
	else {
		cout << setw(PADDING) << " " << setw(CONSOLE_WIDTH) << left << data_info << endl; // Message
		setColor(white);
		cout << setw(PADDING) << " " << left << setw(CONSOLE_WIDTH) << message.text_message << endl; // Message
	}
	setColor(white);
}

// Load a message from a file
// Example: pepe 1396693594 Carlo should line you up for league games! 

void loadMessage(tMessage &message, ifstream &file) {
	char aux;

	file >> message.sender; 
	file >> message.date; 
	file.get(aux); // Skips the blank char
	getline(file, message.text_message); 

}

// Save a message to a file
// Example: pepe 1396693594 Carlo should line you up for league games! 

void saveMessage(const tMessage &message, ofstream &file) 
{
	file << message.sender << " "; // Sender 
	file << message.date << " "; // Date
	file << message.text_message << endl; // Text message
}

// Display Date
// This function makes the Date data, into a human's friendly Version 

string displayDate(tDate date) 
{
	stringstream result;
	tm ltm;
	localtime_s(&ltm, &date);
	result << 1900 + ltm.tm_year << "/" << 1 + ltm.tm_mon << "/" << ltm.tm_mday << ", " << ltm.tm_hour << ":" << ltm.tm_min << ":" << ltm.tm_sec;
	return result.str();
}
