#pragma once

#include <interfaces.h>

enum e_cvar_flags : uint32_t {
	none = 0 << 0,
	hidden = 1 << 4,
	archive = 1 << 7,
	userinfo = 1 << 9,
	never_as_string = 1 << 12,
};

struct c_cvar {
	bool is_command() {
		return util::call_this<bool>(this, 1);
	}

	int32_t get_int() {
		return util::call_this<int32_t>(this, 13, value);
	}

	void set_value(const char* value) {
		util::call_this<void>(this, 14, value);
	}

	void set_value(int32_t value) {
		util::call_this<void>(this, 16, value);
	}

	const char* get_string() const {
		if (this->flags & e_cvar_flags::never_as_string)
			return "";

		const char* str = this->parent->value.string;
		return str ? str : "";
	}

	struct c_value {
		char* string;
		int32_t string_length;
		float fvalue;
		int32_t nvalue;
	};

	char pad_0x0[0x4];
	c_cvar* next;
	bool registered;
	char pad_0x9[0x3];
	const char* name;
	const char* help_string;
	uint32_t flags;
	char pad_0x18[0x4];
	c_cvar* parent;
	const char* default_value;
	c_value value;
	char pad_0x2c[0x34];
};

struct i_engine_convar {
	void unregister_con_command(c_cvar* cvar) {
		util::call_this<void>(this, 11, cvar);
	}

	c_cvar* find_var(const char* name) {
		return util::call_this<c_cvar*>(this, 15, name);
	}
};