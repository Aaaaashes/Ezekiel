#include "error.h"

void displayErrorBox(const char* message) {
#ifdef _WIN32
	size_t size = mbstowcs(NULL, message, 0);
	wchar_t* wideMessage = (wchar_t*)malloc((size + 1) * sizeof(wchar_t));
	mbstowcs(wideMessage, message, size + 1);
	MessageBoxW(NULL, wideMessage, L"Error", MB_ICONERROR | MB_OK);
	free(wideMessage);
#else
	// For Unix-like systems (inc	luding Linux and macOS), you can use a console message
	fprintf(stderr, "%s\n", message);
#endif
}

void assertErr(bool condition, char* message, void (*callback)(),bool crit, ...) {
	if (!condition) {
		va_list args;
		va_start(args, callback);

		(*callback)();

		fatalError(message, crit, args);

		va_end(args);
	}
}

void fatalError(const char* message, bool crit, ...) {
	va_list args;
	va_start(args, message);

	vfprintf(stderr, message, args); // Print the message to stderr

	va_end(args);

	// Display an error box on Windows or print to stderr on Unix-like systems
	if (crit) {
		displayErrorBox(message);

		exit(-1);
	}
}