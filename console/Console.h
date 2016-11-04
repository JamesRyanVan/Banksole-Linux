#ifndef Console_h
#define Console_h

#include <iostream>
#include <unistd.h>

class Console {
public:
	void clear(unsigned int usecs);
	void wait(unsigned int usecs);
};

#endif