#include <string>

using namespace std;


class PrintJob {
};

class PrintJobInfo {

};


class Printer {
private:
	string name;
public:
	PrintJobInfo getJobInfo(PrintJob);
};