#pragma once

#include <cstdint>

#include <modules.h>
#include <util.h>

class c_addresses {
public:
	uintptr_t send_net_msg;
	uintptr_t send_table;
	uintptr_t class_info;
	uintptr_t clamp_bones_in_bbox;
	uintptr_t net_max_payload_bits[4];
	uintptr_t get_channel_encryption_key;
	uintptr_t process_connectionless_packet;
	uintptr_t protocol_version;

	__forceinline void initialize() {
		if (auto ptr = util::pattern_scan(modules->engine, pattern("55 8B EC 83 EC 08 56 8B F1 8B 4D 04")))
			send_net_msg = ptr;
		else if (auto ptr = util::pattern_scan(modules->engine, patternm("BE ? ? ? ? ? 0F 94 C0 ? ? 74 09"))) {
			for (size_t i = 0; i < 0x64; i++) {
				if (*reinterpret_cast<uint8_t*>(ptr - i) == 0x55 || *reinterpret_cast<uint8_t*>(ptr - i) == 0xE9) {
					send_net_msg = ptr - i;
					break;
				}
			}
		} else if (auto ptr = util::pattern_scan(modules->engine, patternm("EB 10 E8 ? ? ? ? 84 C0 EB 07"))) {
			for (size_t i = 0; i < 0x64; i++) {
				if (*reinterpret_cast<uint8_t*>(ptr - i) == 0x55 || *reinterpret_cast<uint8_t*>(ptr - i) == 0xE9) {
					send_net_msg = ptr - i;
					break;
				}
			}
		}

		send_table = util::pattern_scan(modules->engine, pattern("55 8B EC 53 56 57 8B 7D 08 8B CF"));
		class_info = util::pattern_scan(modules->engine, pattern("55 8B EC 8B 45 08 53 57"));
		clamp_bones_in_bbox = util::pattern_scan(modules->client, pattern("55 8B EC 83 E4 F8 83 EC 70 56 57 8B F9 89 7C 24 38"));
		protocol_version = util::pattern_scan(modules->engine, patternm("A1 ? ? ? ? 50 FF 77 08"));

		net_max_payload_bits[0] = util::pattern_scan(modules->engine, patternm("8B 46 14 83 F8 ? 7C 22"));
		net_max_payload_bits[1] = util::pattern_scan(modules->engine, patternm("6A ? E9 98 01 00 00"));
		net_max_payload_bits[2] = util::pattern_scan(modules->engine, patternm("6A ? E9 87 01 00 00"));
		net_max_payload_bits[3] = util::pattern_scan(modules->engine, patternm("6A ? E9 64 01 00 00"));

		get_channel_encryption_key = util::pattern_scan(modules->engine, patternm("8B D1 83 BA ? 01 00 00 00 74 03 33 C0"));
		process_connectionless_packet = util::pattern_scan(modules->engine, pattern("55 8B EC 83 E4 F0 81 EC 28 0E"));
	}
};

inline std::unique_ptr<c_addresses> addresses = std::make_unique<c_addresses>();