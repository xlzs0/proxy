#pragma once

#include <common.h>

class c_modules {
public:
	shadow::detail::dynamic_link_library client;
	shadow::detail::dynamic_link_library engine;
	shadow::detail::dynamic_link_library vstdlib;
	shadow::detail::dynamic_link_library tier0;

	__forceinline void initialize() {
		client = shadow::dll("client");
		engine = shadow::dll("engine");
		vstdlib = shadow::dll("vstdlib");
		tier0 = shadow::dll("tier0");
	}
};

inline std::unique_ptr<c_modules> modules = std::make_unique<c_modules>();