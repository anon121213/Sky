#pragma once

#include <memory>

#ifndef SKY_PLATFORM_WINDOWS
	#error Sky only supports Windows!
#endif

#ifdef SKY_ENABLE_ASSERTS
	#define SKY_ASSERT(x, ...) { if(!(x)) { SKY_ERROR("Assertion Failed: {0}", __VA__ARGS__); __debugbreake(); } }
	#define SKY_CORE_ASSERT(x, ...) { if(!(x)) { SKY_CORE_ERROR("Assertion Failed: {0}", __VA__ARGS__); __debugbreake(); } }
#else
	#define SKY_ASSERT(x, ...)
	#define SKY_CORE_ASSERT(x, ...)
#endif 


#define BIT(x) (1 << x)

#define SKY_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return fn(std::forward<decltype(args)>(args)...); }

namespace Sky {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}