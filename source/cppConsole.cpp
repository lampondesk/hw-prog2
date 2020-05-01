#include <iostream>
#include <cppConsole.hpp>

void TerminalHandler::getCommand() {
	if (!std::cin.eof()) {
		std::cout << std::flush;
		std::getline(std::cin, prompt);
	} else {
		prompt = "-exit";
	}
}
