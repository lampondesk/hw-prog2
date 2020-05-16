#include <iostream>
#include <locale>
#include <cppStructures.hpp>
#include <cppStatus.hpp>
#include <cppExporter.hpp>
#include <cppConsole.hpp>
#include <cppImport.hpp>
#include <memtrace.h>

int main(int argc, char** argv) {
	TerminalHandler		console;
	ImportHandler		ifile;
	contactStore		memStorage;
	bool				DEBUG = false;
	std::string			currentfile;

    std::cout << "cppKontakte v.0.7.1" << std::endl;
	std::cout << "General commands are: " << std::endl;
	std::cout << "add\t\t | Add a new person to the contact list." << std::endl;
	std::cout << "edit\t\t | Edit an already existing person." << std::endl;
	std::cout << "delete\t\t | Delete an already existing person." << std::endl;
	std::cout << "search\t\t | Search for exact or similar data." << std::endl;
	std::cout << "File management commands are: " << std::endl;
	std::cout << "open\t\t | Open the default file or the one supplied via the '-f' option." << std::endl;
	std::cout << "export csv\t | Export the contact list into a stadard csv file." << std::endl;
	std::cout << "export vcard\t | Export the contact list into a stadard VCard file." << std::endl;
	std::cout << "-exit\t\t | Close the application." << std::endl;
	std::cout << "Note: the file is saved automatically after each change." << std::endl << std::endl;
    setlocale(LC_ALL, "");

	while(console.getLoop()) {
		console.getCommand();
		if (console.lastCommand() == "-exit") {
			console.setLoop(false);
		} else if (console.lastCommand() == "-debug") {
			DEBUG = !DEBUG;
			std::cout << "[Debug] Toggled debug mode." << std::endl;
		} else if (console.lastCommand() == "open") {
			try {
				if (argc >= 3 && std::string(argv[1]) == "-f") {
					currentfile = std::string(argv[2]);
					ifile.initFile(currentfile);
				} else {
					currentfile = "cppkontakte.dat.csv";
					ifile.initFile(currentfile);
				}
				ifile.readContacts(memStorage);
			} catch (int e) {
				if (e == CPPKONTAKTE_FILE_IO_ERROR) {
					std::cout << "Error: the requested or the default file cannot be opened." << std::endl;
				} else if (e == CPPKONTAKTE_FILE_CORRUPT) {
					std::cout << "Fatal error: the requested or the default file is corrupt.\nThe app will exit now." << std::endl;
					return CPPKONTAKTE_FILE_CORRUPT;
				} else if (e == CPPKONTAKTE_MEMORY_ALLOC_ERROR) {
					std::cout << "Fatal error: memory error: this either means that there is a bug\nin the software, or you are out of memory." << std::endl;
				}
			}
		} else if (console.lastCommand() == "export csv") {
			if (ifile.isOpen()) {
				try {
					Exporter ocsv;
					ocsv.initFile("oucsv.csv");
					ocsv.outCsv(true, memStorage);
					ocsv.~Exporter();
				} catch (int e) {
					if (e == CPPKONTAKTE_FILE_IO_ERROR) {
						std::cout << "Error: export failed: export target file cannot be opened.";
					}
				}
			} else {
				std::cout << "No file has been opened yet." << std::endl;
			}
		} else if (console.lastCommand() == "export vcard") {
			if (ifile.isOpen()) {
				try {
					Exporter ovcf;
					ovcf.initFile("ouvcard.vcf");
					ovcf.outVcard(memStorage);
					ovcf.~Exporter();
				} catch (int e) {
					if (e == CPPKONTAKTE_FILE_IO_ERROR) {
						std::cout << "Error: export failed: export target file cannot be opened.";
					}
				}
			} else {
				std::cout << "No file has been opened yet." << std::endl;
			}
		} else if (console.lastCommand() == "new") {
			if(ifile.isOpen()) {
				console.consoleAdd(memStorage);
				try {
					Exporter self;
					self.initFile(currentfile);
					self.outCsv(1, memStorage);
					self.~Exporter();
				} catch (int e) {
					if (e == CPPKONTAKTE_FILE_IO_ERROR) {
						std::cout << "Error: file sync failed: file cannot be opened.";
					}
				}
			} else {
				std::cout << "No file has been opened yet" << std::endl;
			}
		} else if (console.lastCommand() == "edit") {
			if(ifile.isOpen()) {
				console.consoleEdit(memStorage);
				try {
					Exporter self;
					self.initFile(currentfile);
					self.outCsv(1, memStorage);
					self.~Exporter();
				} catch (int e) {
					if (e == CPPKONTAKTE_FILE_IO_ERROR) {
						std::cout << "Error: file sync failed: file cannot be opened.";
					}
				}
			} else {
				std::cout << "No file has been opened yet" << std::endl;
			}
		} else if (console.lastCommand() == "delete") {
			if(ifile.isOpen()) {
				console.consoleDelete(memStorage);
				try {
					Exporter self;
					self.initFile(currentfile);
					self.outCsv(1, memStorage);
					self.~Exporter();
				} catch (int e) {
					if (e == CPPKONTAKTE_FILE_IO_ERROR) {
						std::cout << "Error: file sync failed: file cannot be opened.";
					}
				}
			} else {
				std::cout << "No file has been opened yet" << std::endl;
			}
		} else if (console.lastCommand() == "search") {
			if(ifile.isOpen()) {
				console.consoleSearch(memStorage);
			} else {
				std::cout << "No file has been opened yet" << std::endl;
			}
		} else {
			std::cout << "Unknown command." << std::endl;
		}
	}
    return 0;
}
