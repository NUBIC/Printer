#include <stdexcept>

using namespace std;

class SpoolException : public runtime_error {
public:
	explicit SpoolException(const char *_Message)
		: runtime_error(_Message){}
};