#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wchar.h>

#ifdef _WIN32
#include <windows.h>
//#define UNICODE
//#define _UNICODE
#endif




void displayErrorBox(const char* message);

void fatalError(const char* message, bool crit, ...);

void assertErr(bool condition, char* message, void (*callback)(), bool crit, ...);
