#ifndef IMPORT_H
#define IMPORT_H

#include <iostream>
#include <fstream>
#include <cppStructures.hpp>

class ImportHandler {
	std::ifstream inputFile;
	std::string filePath;
	bool open;
public:
	ImportHandler() { open = false; }
	void initFile(std::string);
	void readContacts(contactStore& cs);
	bool isOpen() { return open; }
	~ImportHandler();
};

#endif
