#include <iostream>

class TerminalHandler {
	std::string prompt;
	bool loop;
public:
	TerminalHandler(std::string p = "") : prompt(p) {}
	int getCommand();
	bool getLoop() { return loop; }
	void setLoop(bool b) { loop = b; }
	std::string lastCommand();
};
