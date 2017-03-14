#pragma once

#ifdef _WIN32
#  define DYLIB __declspec( dllexport )
#else
#  define DYLIB
#endif