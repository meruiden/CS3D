#pragma once

#ifdef _WIN32
#define PLATFORM_WINDOWS
#elif defined(unix) || defined(__unix__) || defined(__unix) && !defined(__APPLE__)
#define PLATFORM_LINUX
#elif defined(__APPLE__)
#define PLATFORM_APPLE
#endif

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_APPLE)
#include <sys/time.h>
#include <stddef.h>
#endif

inline double getMiliSeconds()
{
#ifdef PLATFORM_WINDOWS
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
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_APPLE)
	timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000) + (time.tv_usec / 1000);
#endif
	return -1;
}

#if defined PLATFORM_APPLE
#include <ApplicationServices/ApplicationServices.h>
#elif defined PLATFORM_LINUX
#include <X11/Xlib.h>
#endif

inline void setCursorPosition(int x, int y)
{
#if defined PLATFORM_WINDOWS
	BOOL result = SetCursorPos(x, y);
#elif defined PLATFORM_APPLE
	CGPoint new_pos;
	CGEventErr err;
	new_pos.x = x;
	new_pos.y = y;
	err = CGWarpMouseCursorPosition(new_pos);
#elif defined PLATFORM_LINUX
	Display *dpy;
	Window root_window;

	dpy = XOpenDisplay(0);
	root_window = XRootWindow(dpy, 0);
	XSelectInput(dpy, root_window, KeyReleaseMask);
	XWarpPointer(dpy, None, root_window, 0, 0, 0, 0, x, y);
	XFlush(dpy);
#endif

}