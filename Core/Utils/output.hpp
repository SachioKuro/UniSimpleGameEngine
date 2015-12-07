#pragma once


#define ERROR_OUTPUT_ENABLED 1
#define DEBUG_OUTPUT_ENABLED 1

#if ERROR_OUTPUT_ENABLED
	#define ERROR(error) fprintf(stderr, error)
#else
	#define ERROR(error)
#endif

#if DEBUG_OUTPUT_ENABLED
	#define DEBUG(debug) std::cout << debug << std::endl
	#define DEBUG_BOOL(debug) std::cout << std::boolalpha << debug << std::endl
#else
	#define DEBUG(debug)
	#define DEBUG_BOOL(debug)
#endif