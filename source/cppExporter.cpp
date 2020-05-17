#include <iostream>
#include <fstream>
#include <cppExporter.hpp>

void Exporter::initFile(std::string in) {
	outputFile.open(in, std::ios::out | std::ios::binary);
	if (outputFile.fail()) {
		throw CPPKONTAKTE_FILE_IO_ERROR;
	} else {
		filePath = in;
	}
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

void Exporter::outVcard(contactStore& cs) {
	for (size_t i = 0; i < cs.getQuantity(); i++) {
		outputFile << "BEGIN:VCARD" << std::endl;
		outputFile << "VERSION:3.0" << std::endl;
		outputFile << "N:" << cs[i].getLastName() << ";" << cs[i].getFirstName() << ";;;" << std::endl;
		outputFile << "FN:" << cs[i].getFirstName() << " " << cs[i].getLastName() << std::endl;
		outputFile << "EMAIL;type=INTERNET;type=pref:" << cs[i].getEmail() << std::endl;
		outputFile << "TEL;type=CELL;type=VOICE;type=pref:" << cs[i].getTel() << std::endl;
		outputFile << "NOTE:" << cs[i].getComments() << std::endl;
		outputFile << "ADR;type=HOME;type=pref:;;" << cs[i].getAddrStreet() << " ";
		outputFile << cs[i].getAddrNum() << ";";
		outputFile << cs[i].getTown() << ";";
		outputFile << cs[i].getState() << ";";
		outputFile << cs[i].getPostal() << ";";
		outputFile << cs[i].getCountry() << std::endl;
		outputFile << "END:VCARD" << std::endl;
	}
}

Exporter::~Exporter() {
	outputFile.close();
}