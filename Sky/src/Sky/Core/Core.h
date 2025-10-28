#pragma once

#include <memory>

#ifdef SKY_PLATFORM_WINDOWS 
#if SKY_DYNAMIC_LINK
	#ifdef SKY_BUILD_DLL
		#define SKY_API __declspec(dllexport)
	#else
		#define SKY_API __declspec(dllimport)
	#endif
#else
	#define SKY_API	
#endif 
#else
	#error Sky only support Windows!
#endif 

#ifdef SKY_ENABLE_ASSERTS
	#define SKY_ASSERT(x, ...) { if(!(x)) { SKY_ERROR("Assertion Failed: {0}", __VA__ARGS__); __debugbreake(); } }
	#define SKY_CORE_ASSERT(x, ...) { if(!(x)) { SKY_CORE_ERROR("Assertion Failed: {0}", __VA__ARGS__); __debugbreake(); } }
#else
	#define SKY_ASSERT(x, ...)
	#define SKY_CORE_ASSERT(x, ...)
#endif 


#define BIT(x) (1 << x)

#define SKY_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Sky {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}