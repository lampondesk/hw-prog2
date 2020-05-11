#include <iostream>
#include <fstream>
#include <cppImport.hpp>
#include <cppStructures.hpp>

void ImportHandler::initFile(std::string in) {
	inputFile.open(in, std::ios::out | std::ios::binary);
	filePath = in;
}
void ImportHandler::readContacts(contactStore& cs) {
	std::string currentLine;
	char* c_currentLine = const_cast<char*>(currentLine.c_str());
	cppContact tempContact;
	while(getline(inputFile, currentLine)) {
		char* tokenisedString = strtok(c_currentLine, ",");
		tempContact.setData(tokenisedString, "id");
		tokenisedString = strtok(NULL, ",");
		tempContact.setData(tokenisedString, "firstName");
		tokenisedString = strtok(NULL, ",");
		tempContact.setData(tokenisedString, "lastName");
		tokenisedString = strtok(NULL, ",");
		tempContact.setData(tokenisedString, "tel");
		tokenisedString = strtok(NULL, ",");
		tempContact.setData(tokenisedString, "email");
		tokenisedString = strtok(NULL, ",");
		tempContact.setData(tokenisedString, "comments");
		tokenisedString = strtok(NULL, ",");
		tempContact.setData(tokenisedString, "addrStreet");
		tokenisedString = strtok(NULL, ",");
		tempContact.setData(tokenisedString, "addrNum");
		tokenisedString = strtok(NULL, ",");
		tempContact.setData(tokenisedString, "town");
		tokenisedString = strtok(NULL, ",");
		tempContact.setData(tokenisedString, "state");
		tokenisedString = strtok(NULL, ",");
		tempContact.setData(tokenisedString, "country");
		tokenisedString = strtok(NULL, ",");
		tempContact.setData(tokenisedString, "postal");
		cs.addContact(tempContact);
	}
}
ImportHandler::~ImportHandler() {
	inputFile.close();
}