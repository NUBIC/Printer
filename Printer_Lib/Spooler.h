#ifndef SPOOLER_H
#define SPOOLER_H

#include <string>

using namespace std;

class Spooler {
private:
	string foo;

public:
	static bool spool(string printerName, string filePath);

};

#endif /* SPOOLER_H */