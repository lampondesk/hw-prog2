#include <iostream>
#include <locale>
#include <string.h>
#include <cppStructures.hpp>
#include <cppStatus.hpp>
#include <cppExporter.hpp>
#include <cppConsole.hpp>
#include <cppImport.hpp>
#include <memtrace.h>

int main(int argc, char** argv) {

	/*					Initialisation: objects					*/
	TerminalHandler		console;
	ImportHandler		ifile;
	contactStore		memStorage;
	bool				DEBUG = false;


	/*					Initialisation: main loop				*/
    std::cout << "cppKontakte v.0.3.3" << std::endl;
    setlocale(LC_ALL, "");

	while(console.getLoop()) {
		console.getCommand();
		if (console.lastCommand() == "-exit") {
			console.setLoop(false);
		} else if (console.lastCommand() == "-debug") {
			DEBUG = !DEBUG;
			std::cout << "[Debug] Toggled debug mode." << std::endl;
		} else if (console.lastCommand() == "open") {
			if (argc >= 3 && strcmp(argv[1], "-f") == 0) {
				ifile.initFile(std::string(argv[2]));
			} else {
				ifile.initFile("cppkontakte.dat.csv");
			}
			try {
				ifile.readContacts(memStorage);
			} catch (int) {
				std::cout << "The file seems to be corrupt. Aborting." << std::endl;
				return CPPKONTAKTE_FILE_CORRUPT;
			}
		} else if (console.lastCommand() == "export csv") {
			if (ifile.isOpen()) {
				Exporter ocsv;
				ocsv.initFile("oucsv.csv");
				ocsv.outCsv(true, memStorage);
			} else {
				std::cout << "No file has been opened yet." << std::endl;
			}
		} else if (console.lastCommand() == "export vcard") {
			if (ifile.isOpen()) {
				Exporter ovcf;
				ovcf.initFile("ouvcard.vcf");
				ovcf.outVcard(memStorage);
			} else {
				std::cout << "No file has been opened yet." << std::endl;
			}
		}
	}

    return 0;
}
