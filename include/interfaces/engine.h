#pragma once

#include <util.h>

struct i_engine_client {
	__forceinline void execute_client_cmd(const char* cmd) {
		util::call_this<void>(this, 114, cmd, false);
	}
};