#include <iostream>
#include <locale>
#include <cppStructures.hpp>
#include <cppStatus.hpp>
#include <cppExporter.hpp>
#include <cppConsole.hpp>
#include <memtrace.h>

int main() {

	/*					Initialisation: objects					*/
	TerminalHandler		console;
	int					DEBUG = 0;


	/*					Initialisation: main loop				*/
    std::cout << "cppKontakte v.0.0.1" << std::endl;
    setlocale(LC_ALL, "");

	while(console.getLoop()) {
		console.getCommand();
		if (console.lastCommand() == "-exit") {
			console.setLoop(false);
		} else if (console.lastCommand() == "-debug") {
			DEBUG = !DEBUG;
			std::cout << "[Debug] Toggled debug mode." << std::endl;
		}
	}

    return 0;
}
