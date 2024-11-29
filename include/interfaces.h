#pragma once

#include "interfaces/client_state.h"
#include "interfaces/cvar.h"
#include "interfaces/engine.h"
#include "interfaces/game_console.h"

#include <util.h>
#include <modules.h>

class c_interfaces {
	using create_interface_t = void* (__cdecl*)(const char*, int32_t*);

	template<typename T>
	T* get_interface(shadow::hash64_t module_name, const char* interface_name) {
		auto create_interface = shadow::address_t{ shadow::dll_export("CreateInterface", module_name).address() }.as<create_interface_t>();
		return reinterpret_cast<T*>(create_interface(interface_name, nullptr));
	}
public:
	c_client_state* client_state;
	i_engine_client* engine;
	i_engine_convar* convar;
	i_game_console* console;

	__forceinline void initialize() {
		client_state = **reinterpret_cast<c_client_state***>(util::pattern_scan(modules->engine, patternm("A1 ? ? ? ? 8B 88 ? ? ? ? 85 C9 75 07")) + 1);
		engine = get_interface<i_engine_client>("engine", "VEngineClient014");
		convar = get_interface<i_engine_convar>("vstdlib", "VEngineCvar007");
		console = get_interface<i_game_console>("client", "GameConsole004");
	}
};

inline std::unique_ptr<c_interfaces> interfaces = std::make_unique<c_interfaces>();