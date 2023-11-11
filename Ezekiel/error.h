#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>


void assertErr(bool condition, char* message, void (*callback)());

void fatalError(char* message);