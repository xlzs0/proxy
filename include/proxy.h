#pragma once

#include <common.h>

class c_proxy {
	static DWORD WINAPI init_thread(void*);
public:
	void initialize();
	void shutdown();
};

inline std::unique_ptr<c_proxy> proxy = std::make_unique<c_proxy>();