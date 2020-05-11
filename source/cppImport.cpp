#include <iostream>
#include <fstream>
#include <string.h>
#include <cppImport.hpp>
#include <cppStatus.hpp>
#include <cppStructures.hpp>

void ImportHandler::initFile(std::string in) {
	inputFile.open(in, std::ios::out | std::ios::binary);
	filePath = in;
}
void ImportHandler::readContacts(contactStore& cs) {
	std::string currentLine;
	cppContact tempContact;
	while(getline(inputFile, currentLine)) {
		char* c_currentLine = const_cast<char*>(currentLine.c_str());
		char* tokenisedString = strtok(c_currentLine, ",");
		int i = 0;
		while(tokenisedString != NULL && i < 12) {
			tempContact.setData(tokenisedString, i);
			tokenisedString = strtok(NULL, ",");
			i++;
		}
		if (i != 12) {
			throw CPPKONTAKTE_FILE_CORRUPT;
			cs.~contactStore();
			break;
		}
		cs.addContact(tempContact);
	}
}
ImportHandler::~ImportHandler() {
	inputFile.close();
}