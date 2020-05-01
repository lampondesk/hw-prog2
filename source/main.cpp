#include <iostream>
#include <locale>
#include <cppStructures.hpp>
#include <cppStatus.hpp>
#include <cppExporter.hpp>
#include <cppConsole.hpp>

int main() {

	/*					Initialisation: objects					*/
	TerminalHandler		console;


	/*					Initialisation: main loop				*/
    std::cout << "cppKontakte v.0.0.1" << std::endl;
    setlocale(LC_ALL, "");

	while(console.getLoop()) {
		console.getCommand();
		if (console.lastCommand() == "-exit") {
			console.setLoop(false);
		}
	}

    return 0;
}
