#pragma once

#ifdef ARC_PLATFORM_WINDOWS
#if ARC_DYNAMIC_LINK
	#ifdef ARC_BUILD_DLL
		#define ARC_API __declspec(dllexport)
	#else
		#define ARC_API __declspec(dllimport)
	#endif
#else
	#define ARC_API
#endif
#else
	#error Arc only supports Windows
#endif

#ifdef ARC_DEBUG
	#define ARC_ENABLE_ASSERTS
#endif

#ifdef ARC_ENABLE_ASSERTS
	#define ARC_ASSERT(x, ...) {if(!(x)) {ARC_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define ARC_CORE_ASSERT(x, ...) {if(!(x)) {ARC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ARC_ASSERT(x, ...)
	#define ARC_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x) // bitfield

//binds the Event "member" function to the EventCallbackFn
#define ARC_BIND_EVENT_FN(function) std::bind(&function, this, std::placeholders::_1)
