#pragma once

#ifdef _WIN32
#include <Windows.h>
#elif defined(unix) || defined(__unix__) || defined(__unix) || defined(__APPLE__)
#include <sys/time.h>
#include <stddef.h>
#endif

class CS3DTime{
public:
	static double getMiliSeconds();
};

