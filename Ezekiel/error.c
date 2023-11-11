#include "error.h"

void assertErr(bool condition, char* message, void (*callback)(), ...) {
	if (!condition) {
		va_list args;
		va_start(args, callback);

		(*callback)();

		fatalError(message, args);

		va_end(args);
	}
}

void fatalError(char* message, ...) {
	va_list args;
	va_start(args, message);

	vfprintf(stderr, message, args); // You can use vfprintf to print the message to stderr

	va_end(args);
	exit(-1);
}