#include <iostream>
#include <cppStructures.hpp>

class TerminalHandler {
	std::string prompt;
	bool loop;
	std::string* askData(contactStore& cs); 
	bool validateEmail(const char*);
	bool validatePhone(const char*);
	bool validatePostal(const char*);
	bool generalValidation(const char*);
	void display(cppContact&);
public:
	TerminalHandler(bool b = true) : loop(b) {}
	void getCommand();
	void consoleAdd(contactStore& cs);
	void consoleEdit(contactStore& cs);
	void consoleDelete(contactStore& cs);
	void consoleSearch(contactStore& cs);
	void displayAll(contactStore& cs);
	bool getLoop() { return loop; }
	void setLoop(bool b) { loop = b; }
	std::string lastCommand() { return prompt; }
};
