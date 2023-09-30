#pragma once

#ifdef _PLATFORM_WINDOWS
	#ifdef _BUILD_DLL
		#define _API __declspec(dllexport)
	#else
		#define _API __declspec(dllimport)
	#endif // _BUILD_DLL
#else 
	#error only supports windows!
#endif // _PLATFORM_WINDOWS