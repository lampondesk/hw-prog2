#include <iostream>
#include <fstream>
#include <string.h>
#include <cppImport.hpp>
#include <cppStatus.hpp>
#include <cppStructures.hpp>

void ImportHandler::initFile(std::string in) {
	inputFile.open(in, std::ios::in | std::ios::out | std::ios::binary); 
	if(inputFile.fail()) {
		inputFile.close();
		inputFile.open(in, std::ios::out | std::ios::app | std::ios::binary);
		inputFile.close();
		inputFile.open(in, std::ios::in | std::ios::out | std::ios::binary); 
		if (inputFile.fail()) {
			throw CPPKONTAKTE_FILE_IO_ERROR;
		}
	}
	filePath = in;
	open = true;
}
void ImportHandler::readContacts(contactStore& cs) {
	std::string currentLine; 
	cppContact tempContact;
	while(getline(inputFile, currentLine)) {
		char* c_currentLine = const_cast<char*>(currentLine.c_str());
		char* tokenisedString = strtok(c_currentLine, ",");
		int i = 0;
		while(tokenisedString != NULL) {
			try {
				tempContact.setData(tokenisedString, i);
			} catch (int) {
				throw CPPKONTAKTE_FILE_CORRUPT;
			}
			tokenisedString = strtok(NULL, ",");
			i++;
		}
		if (i < 12) {
			throw CPPKONTAKTE_FILE_CORRUPT;
			break;
		}
		try {
			cs.addContact(tempContact);
		} catch (int e) {
			throw e;
		}
	}
}
ImportHandler::~ImportHandler() {
	inputFile.close();
}