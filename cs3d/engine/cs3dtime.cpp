#include <engine/cs3dtime.h>

double CS3DTime::getMiliSeconds()
{
#ifdef _WIN32
	static LARGE_INTEGER s_frequency;
	static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
	if (s_use_qpc)
	{
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);
		return (1000LL * now.QuadPart) / s_frequency.QuadPart;
	}
	else
	{
		return GetTickCount();
	}
#elif defined(unix) || defined(__unix__) || defined(__unix) || defined(__APPLE__)
	timeval time;
	gettimeofday(&time, NULL);
    std::cout << time.tv_sec  << std::endl;
	return (time.tv_sec * 1000) + (time.tv_usec / 1000);
#endif
    return -1;
}
