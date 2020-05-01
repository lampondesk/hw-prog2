#include <iostream>

class TerminalHandler {
	std::string prompt;
	bool loop;
public:
	TerminalHandler(std::string p = "", bool b = true) : prompt(p), loop(b) {}
	void getCommand();
	bool getLoop() { return loop; }
	void setLoop(bool b) { loop = b; }
	std::string lastCommand() { return prompt; }
};
