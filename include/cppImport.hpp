#ifndef IMPORT_H
#define IMPORT_H

#include <iostream>
#include <fstream>
#include <cppStructures.hpp>

class ImportHandler {
	std::ifstream inputFile;
	std::string filePath;
	size_t lines;
public:
	void initFile(std::string);
	void writeContacts();
	void readContacts(contactStore& cs);
	size_t getFileLen() { return lines; };
	~ImportHandler();
};

#endif
