#ifndef EXPORTER_H
#define EXPORTER_H

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
