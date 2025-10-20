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

#ifdef SKY_ENABLE_ASSERTS
	#define SKY_ASSERT(x, ...) { if(!(x)) { SKY_ERROR("Assertion Failed: {0}", __VA__ARGS__); __debugbreake(); } }
	#define SKY_CORE_ASSERT(x, ...) { if(!(x)) { SKY_CORE_ERROR("Assertion Failed: {0}", __VA__ARGS__); __debugbreake(); } }
#else
	#define SKY_ACCERT(x, ...)
	#define SKY_CORE_ACCERT(x, ...)
#endif 


#define BIT(x) (1 << x)

#define SKY_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)