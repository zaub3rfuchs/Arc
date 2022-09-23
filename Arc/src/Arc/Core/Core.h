#pragma once

#include "Arc/Core/PlatformDetection.h"
#include "Ref.h"
#include <memory>

#ifdef ARC_DEBUG
	#if defined(ARC_PLATFORM_WINDOWS)
		#define ARC_DEBUGBREAK() __debugbreak()
	#elif defined(ARC_PLATFORM_LINUX)
		#include <signal.h>
		#define ARC_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define ARC_ENABLE_ASSERTS
#else
	#define ARC_DEBUGBREAK()
#endif

#define ARC_EXPAND_MACRO(x) x
#define ARC_STRINGIFY_MACRO(x) #x


#define BIT(x) (1 << x) // bitfield

//binds the Event "member" function to the EventCallbackFn
//#define ARC_BIND_EVENT_FN(function) std::bind(&function, this, std::placeholders::_1)
#define ARC_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace ArcEngine {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	//template<typename T>
	//using Ref = std::shared_ptr<T>;
	//template<typename T, typename ... Args>
	//constexpr Ref<T> CreateRef(Args&& ... args)
	//{
	//	return std::make_shared<T>(std::forward<Args>(args)...);
	//}
}

#include "Arc/Core/Assert.h"
