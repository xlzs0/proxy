#pragma once

#include <common.h>

#include <vector>
#include <string>

#define patternm(pattern) ([](){ static constexpr auto bytes = util::internal::pattern_to_bytes<util::internal::count_bytes(pattern)>(pattern); return bytes; }()), ([](){ static constexpr auto mask = util::internal::pattern_to_mask<util::internal::count_bytes(pattern)>(pattern); return mask; }())
#define pattern(pattern) ([](){ static constexpr auto bytes = util::internal::pattern_to_bytes<util::internal::count_bytes(pattern)>(pattern); return bytes; }())

namespace util {
	namespace internal {
		__forceinline constexpr size_t strlen(const char* string) {
			size_t size = 0;
			while (*string++)
				size++;
			return size;
		}

		__forceinline constexpr bool is_hex_digit(char c) {
			return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
		}

		__forceinline constexpr uint8_t parse_byte(char high, char low) {
			auto to_digit = [](char c) constexpr -> uint8_t {
				return (c >= '0' && c <= '9') ? c - '0' : (c >= 'A' && c <= 'F') ? c - 'A' + 10 : (c >= 'a' && c <= 'f') ? c - 'a' + 10 : 0;
			};

			return (to_digit(high) << 4) | to_digit(low);
		}

		__forceinline constexpr size_t count_bytes(const char* str) {
			size_t count = 0;
			for (size_t i = 0; i < strlen(str); i++) {
				if (str[i] == ' ')
					i++;

				if (is_hex_digit(str[i])) {
					if (str[i + 1] && is_hex_digit(str[i + 1])) {
						++count;
						++i;
					}
				}
				else if (str[i] == '?')
					++count;
			}
			return count;
		}

		template<size_t bytes>
		__forceinline constexpr auto pattern_to_bytes(const char* pattern) {
			std::array<uint8_t, bytes> arr;
			size_t index = 0;

			for (size_t i = 0; i < strlen(pattern); i++) {
				if (pattern[i] == ' ')
					continue;

				if (pattern[i] == '?') {
					arr[index++] = 0x00;
					i += 1;
				}
				else if (pattern[i + 1]) {
					arr[index++] = parse_byte(pattern[i], pattern[i + 1]);
					i += 1;
				}
			}

			return arr;
		}

		template<size_t bytes>
		__forceinline constexpr auto pattern_to_mask(const char* pattern) {
			std::array<uint8_t, bytes> mask = {};
			size_t index = 0;

			for (size_t i = 0; i < strlen(pattern); i++) {
				if (pattern[i] == ' ')
					continue;

				if (pattern[i] == '?') {
					mask[index++] = 0xFF;
					i += 1;
				}
				else if (pattern[i + 1] && is_hex_digit(pattern[i]) && is_hex_digit(pattern[i + 1])) {
					mask[index++] = 0x00;
					i += 1;
				}
			}

			return mask;
		}
	}

	template<typename t>
	__forceinline void memcpy(t address, const void* buf, const size_t size) {
		DWORD old_protect{};
		VirtualProtect(reinterpret_cast<void*>(address), size, 0x40, &old_protect);
		::memcpy(reinterpret_cast<void*>(address), buf, size);
		VirtualProtect(reinterpret_cast<void*>(address), size, old_protect, &old_protect);
	}

	template<typename t>
	__forceinline void memset(t address, int byte, size_t size) {
		DWORD old_protect{};
		VirtualProtect(reinterpret_cast<void*>(address), size, 0x40, &old_protect);
		::memset(reinterpret_cast<void*>(address), byte, size);
		VirtualProtect(reinterpret_cast<void*>(address), size, old_protect, &old_protect);
	}

	template<typename... args_t>
	__forceinline void con_msg(const char* msg, args_t... args) {
		using con_msg_t = void(*)(const char*, ...);
		static auto con_msg = shadow::dll_export("?ConMsg@@YAXPBDZZ", "tier0").address().as<con_msg_t>();

		if (con_msg)
			con_msg(msg, args...);
	}

	template<size_t pattern_size>
	__declspec(noinline) inline uintptr_t pattern_scan(const shadow::detail::dynamic_link_library& dll, std::array<uint8_t, pattern_size> pattern) {
		const auto data = dll.base_address().as<uint8_t*>();
		const auto image_size = dll.image()->get_optional_header()->size_image;
		
		for (size_t i = 0; i < (image_size - pattern.size()); ++i) {
			size_t size = 0;
			while ((data + i)[size] == pattern[size]) {
				if (++size > pattern.size() - 1)
					return reinterpret_cast<uintptr_t>(data + i);
			}
		}

		return NULL;
	}

	template<size_t pattern_size>
	__declspec(noinline) inline uintptr_t pattern_scan(const shadow::detail::dynamic_link_library& dll, std::array<uint8_t, pattern_size> pattern, std::array<uint8_t, pattern_size> mask) {
		const auto data = dll.base_address().as<uint8_t*>();
		const auto image_size = dll.image()->get_optional_header()->size_image;

		for (size_t i = 0; i < (image_size - pattern.size()); ++i) {
			size_t size = 0;
			while ((data + i)[size] == pattern[size] || mask[size] == 0xFF) {
				if (++size > mask.size() - 1)
					return reinterpret_cast<uintptr_t>(data + i);
			}
		}

		return NULL;
	}

	template <typename ret_t, typename ... args_t>
	__forceinline constexpr ret_t call_this(void* instance, size_t index, args_t... args) {
		using fn_t = ret_t(__thiscall*)(void*, args_t...);
		auto vtable = *static_cast<fn_t**>(instance);
		return vtable[index](instance, args...);
	}
}