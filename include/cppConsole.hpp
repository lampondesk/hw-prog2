#include <iostream>

class TerminalHandler {
	std::string prompt;
public:
	TerminalHandler(std::string p = "") : prompt(p) {}
	int getCommand();
	std::string lastCommand();
};
