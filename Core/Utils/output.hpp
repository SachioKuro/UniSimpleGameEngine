#pragma once

#include <stdio.h>
#include <iostream>
#include <iomanip>

/* Output-Makros */

#ifndef ERROR_OUTPUT_ENABLED
	#define ERROR_OUTPUT_ENABLED 1
#endif

#ifndef DEBUG_OUTPUT_ENABLED
	#define DEBUG_OUTPUT_ENABLED 1
#endif

#ifndef INFORMATION_OUTPUT_ENABLED
	#define INFORMATION_OUTPUT_ENABLED 1
#endif


#if ERROR_OUTPUT_ENABLED
	#define ERROR(error) fprintf(stderr, error)
	#define ERROR_F(...) fprintf(stderr, __VA_ARGS__)
#else
	#define ERROR(error)
#endif

#if DEBUG_OUTPUT_ENABLED
	#define DEBUG(debug) std::cout << debug << std::endl
	#define DEBUG_F(...) fprintf(stdout, __VA_ARGS__)
	#define DEBUG_BOOL(debug) std::cout << std::boolalpha << debug << std::endl
#else
	#define DEBUG(debug)
	#define DEBUG_F(debug)
	#define DEBUG_BOOL(debug)
#endif

#if INFORMATION_OUTPUT_ENABLED 
	#define INFO(info) std::cout << info << std::endl
	#define INFO_F(...) fprintf(stdout, __VA_ARGS__)
#else
	#define INFO(info)
	#define INFO_F(info)
#endif