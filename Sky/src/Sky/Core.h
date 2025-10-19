#pragma once

#ifdef SKY_PLATFORM_WINDOWS 
	#ifdef SKY_BUILD_DLL
		#define SKY_API __declspec(dllexport)
	#else
		#define SKY_API __declspec(dllimport)
	#endif
#else
	#error Sky only support Windows!
#endif 

#define BIT(x) (1 << x)