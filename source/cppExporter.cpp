#include <iostream>
#include <fstream>
#include <cppExporter.hpp>

void Exporter::initFile(std::string in) {
	outputFile.open(in, std::ios::out | std::ios::binary);
	filePath = in;
}

void Exporter::outCsv(bool copy, contactStore& cs) {
	for (size_t i = 0; i < cs.getQuantity(); i++) {
		outputFile << cs[i].getId() << ",";
		outputFile << cs[i].getFirstName() << ",";
		outputFile << cs[i].getLastName() << ",";
		outputFile << cs[i].getTel() << ",";
		outputFile << cs[i].getEmail() << ",";
		outputFile << cs[i].getComments() << ",";
		outputFile << cs[i].getAddrStreet() << ",";
		outputFile << cs[i].getAddrNum() << ",";
		outputFile << cs[i].getTown() << ",";
		outputFile << cs[i].getState() << ",";
		outputFile << cs[i].getCountry() << ",";
		outputFile << cs[i].getPostal();
		outputFile << std::endl;
	}
}

Exporter::~Exporter() {
	outputFile.close();
}