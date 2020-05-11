#ifndef EXPORT_H
#define EXPORT_H

#include <iostream>
#include <fstream>

class Exporter {
	std::ofstream output;
public:
	Exporter();
	int outCsv();
	int outVcard();
	~Exporter();
};

#endif
