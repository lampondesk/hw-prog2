#include <iostream>
#include <cppConsole.hpp>

void TerminalHandler::getCommand() {
	std::getline(std::cin, prompt);
}
