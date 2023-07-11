#pragma once

#ifdef E_PLATFROM_WINDOWS
	#ifdef E_BUILD_DLL
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif

#else
	#error Engine only support windows
#endif


#define BIT(x) ( 1 << x )