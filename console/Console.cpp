#include "Console.h"

void Console::clear(unsigned int usecs) {
    usleep(usecs);
	std::cout << "\033[2J\033[1;1H";
}

void Console::wait(unsigned int usecs) {
    usleep(usecs);
}