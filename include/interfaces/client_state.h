#pragma once

#include <versions.h>

struct c_client_state {
	//char pad[0x4CD0];

	__forceinline uint32_t server_version() const {
		if (versions->local <= 13629)
			return *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x4C54);
		
		return *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x4CCC);
	}
};