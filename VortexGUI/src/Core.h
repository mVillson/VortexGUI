#pragma once

#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>
#include <array>
#include <unordered_map>

#ifdef VTX_BUILD_DLL
	#define VORTEX_API __declspec(dllexport)
#else
	#define VORTEX_API __declspec(dllimport)
#endif // VORTEX_BUILD_DLL