#pragma once

#include <stdio.h>
#include <iostream>
#include <iomanip>

#define ERROR_OUTPUT_ENABLED 1
#define DEBUG_OUTPUT_ENABLED 1

#if ERROR_OUTPUT_ENABLED
	#define ERROR(error) fprintf(stderr, error)
	#define ERROR_F(...) fprintf(stderr, __VA_ARGS__)
#else
	#define ERROR(error)
#endif

#if DEBUG_OUTPUT_ENABLED
	#define DEBUG(debug) std::cout << debug << std::endl
	#define DEBUG_F(...) fprintf(stderr, __VA_ARGS__)
	#define DEBUG_BOOL(debug) std::cout << std::boolalpha << debug << std::endl
#else
	#define DEBUG(debug)
	#define DEBUG_BOOL(debug)
#endif