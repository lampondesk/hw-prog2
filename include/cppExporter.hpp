#ifndef EXPORT_H
#define EXPORT_H

#include <iostream>
#include <fstream>
#include <cppStructures.hpp>

class Exporter {
	std::ofstream	outputFile;
	std::string		filePath;
public:
	void initFile(std::string);
	void outCsv(bool copy, contactStore& cs);
	void outVcard();
	~Exporter();
};

#endif
