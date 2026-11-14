#pragma once
//inclusions
//example :
/*
#include <atomic>
#include <string>
#include <thread>
*/

namespace libraryname { //separated because of readability.
	//forward decalarations like structures
	//example :
	//struct instance_context;

	struct data_types; //never mind. literally it says what i want to say. doesn't it?
	namespace core {
		namespace opearting_system_a1 { //replace it with actual name like win/mac/linux_x11/linux_wayland
			inline data_types function_a1();
			inline data_types function_a2();
			inline data_types function_a3();
		}
		namespace opearting_system_a2 { //same as previous explanation
			inline data_types function_a1();
			inline data_types function_a2();
			inline data_types function_a3();
		}
		namespace opearting_system_a3 { //same as previous explanation
			inline data_types function_a1();
			inline data_types function_a2();
			inline data_types function_a3();
		}
	}
}

namespace libraryname {
	//premise definitions.
	//i most likely define vector structures or instance/screen structures or something like that
	/* 
	//example:
	struct vector2 { float x = 0.f, y = 0.f };
	struct vector3 { float x = 0.f, y = 0.f, z = 0.f; };
	struct vector4 { float x = 0.f, y = 0.f, z = 0.f, w = 0.f; };
	//i often write this on a single line. leaving out float makes it much easier to read.
	*/
	struct data_types {}; //never mind (it's because of forward decaralation part of os-dependent in the code above)

	//contains global/indispensable information.
	namespace database {
		//example :
		//std::atomic<bool> running;
		//the name of the library,
		//the version of the library,
		//instances,
		//HWND/window/void* (if i don't adpot instance-based code.)
		//and stuff something like that
	}

	//literally utility classes. occasionally it can be used as engine/front/user-utilized feature
	class a1_util {
	public:
		static inline bool function_a1(/*arg*/) { return true; };
	};
	//continue

	//handles/transfers to os-dependent handlings
	namespace backend {
		//example :
		/* use transfer_ or directly write the function name (option)
		
		inline void transfer_function_a1(device_list device) {

		//or

		inline void function_a1(device_list device) {

		if (device == device_list::opearting_system_a1) libraryname::core::opearting_system_a1::function_a1();
		else if (device == device_list::opearting_system_a2) libraryname::core::opearting_system_a2::function_a1();
		else if (device == device_list::opearting_system_a3) libraryname::core::opearting_system_a3::function_a1();
		else return; //or add fallback code
		}
		*/
	}

	//class which is expected for being used by users
	class engine {
	public:
		//Example :
		/*
		static inline bool setup() {
		//do something
		return true;
		};

		static inline void shutdown() {
		//do something
		};
		*/
	};
}

//os-dependent inclusions
//example :
/*
#if defined(_WIN32)
#include <windows.h>
#endif
*/

//i usually write like this when temporary processes nothing
inline libraryname::data_types libraryname::core::opearting_system_a1::function_a1() { return {}; }
inline libraryname::data_types libraryname::core::opearting_system_a1::function_a2() { return {}; }
inline libraryname::data_types libraryname::core::opearting_system_a1::function_a3() { return {}; }

//os-dependent inclusions
//example :
/*
#if defined(__APPLE__)
#include <Cocoa/Cocoa.h>
#endif
*/

inline libraryname::data_types libraryname::core::opearting_system_a2::function_a1() { return {}; }
inline libraryname::data_types libraryname::core::opearting_system_a2::function_a2() { return {}; }
inline libraryname::data_types libraryname::core::opearting_system_a2::function_a3() { return {}; }

//os-dependent inclusions
//example :
/*
#if defined(__linux__)
#include <unistd.h>
#endif
*/

//if i write the implementation i write like this
inline libraryname::data_types libraryname::core::opearting_system_a3::function_a1() {
	//example :
	/*
#if defined(__linux__)
	float result = 0.f;
	float a = FLT_MAX;
	float b = FLT_MIN;
	result = a + b;
	return result;
#endif
	return {};
	*/
}

inline libraryname::data_types libraryname::core::opearting_system_a3::function_a2() {
	//example :
	/*
#if defined(__linux__)
	constexpr float idk1 = 140980943.f;
	constexpr float idk2 = 41378401708.f;
	return idk1 + idk2;
	#endif
	return {};
	*/
}

inline libraryname::data_types libraryname::core::opearting_system_a3::function_a3() {
	//im way too lazy for this sorry
}
