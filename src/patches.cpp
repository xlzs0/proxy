#include <addresses.h>
#include <patches.h>
#include <versions.h>

uint8_t last_net_max_payload_bits = -1;

void c_patches::update_max_payload_bits(uint8_t new_bits) {
	uint8_t bits = new_bits > 0 ? new_bits : versions->get_server_bits();
		
	if (last_net_max_payload_bits == bits)
		return;

	last_net_max_payload_bits = bits;

	uint32_t shift = (1 << bits) - 1;
	shift = (shift >> 0x10) & 0xFF;

	std::array<uint8_t, 47> bytes { 0x8B, 0x46, 0x14, 0x83, 0xF8, bits, 0x7C, 0x22, 0x8B, 0x4E, 0x10, 0x8B, 0xD9, 0x81, 0xE3, 0xFF, 0xFF, static_cast<uint8_t>(shift), 0x00, 0x83, 0xC0, static_cast<uint8_t>((0xFF - bits) + 1), 0x89, 0x46, 0x14, 0x0F, 0x84, 0xAF, 0x03, 0x00, 0x00, 0xC1, 0xE9, bits, 0x89, 0x4E, 0x10, 0xE9, 0x34, 0x04, 0x00, 0x00, 0xB9, bits, 0x00, 0x00, 0x00 };

	util::memcpy(addresses->net_max_payload_bits[0], bytes.data(), 0x2F);
	util::memset(addresses->net_max_payload_bits[1] + 0x01, bits, 0x01);
	util::memset(addresses->net_max_payload_bits[2] + 0x01, bits, 0x01);
	util::memset(addresses->net_max_payload_bits[3] + 0x01, bits, 0x01);
}

void c_patches::initialize() {
	update_max_payload_bits(versions->get_target_bits());

	uint8_t bytes[] = { 0xB3, 0x01, 0x90 };
	if (auto ptr = util::pattern_scan(modules->engine, patternm("0F 95 C3 8B 01 FF 50 ? 51 8A D3 E8 ? ? ? ? 83 C4 04 5F")))
		util::memcpy(ptr, bytes, 0x03);

	uint8_t bytes1[] = { 0x89, 0xC8, 0x90 };
	if (auto ptr = util::pattern_scan(modules->engine, patternm("0F 44 C1 B9 ? ? ? ? 50 A1")))
		util::memcpy(ptr, bytes1, 0x03);

	if (auto ptr = util::pattern_scan(modules->engine, pattern("0F 84 00 5B 00 00")))
		util::memset(ptr, 0x90, 0x06);

	if (auto ptr = util::pattern_scan(modules->engine, patternm("C7 86 ? ? ? ? ? ? ? ? C7 86 ? ? ? ? ? ? ? ? C7 86 88 03 00 00 00 00 00 00 C7 86 8C 03 00 00 00 00 00 00")))
		util::memset(ptr, 0x90, 0x0A);

	if (auto ptr = util::pattern_scan(modules->engine, patternm("C7 86 ? ? ? ? ? ? ? ? C7 86 ? ? ? ? ? ? ? ? 85 C9 74 13 8B 01")))
		util::memset(ptr, 0x90, 0x0A);

	uint8_t bytes4[] = { 0xE9, 0x92, 0x00, 0x00, 0x00, 0x90 };
	if (auto ptr = util::pattern_scan(modules->engine, patternm("0F 85 91 00 00 00 8B 0D ? ? ? ? 8B 01")))
		util::memcpy(ptr, bytes4, 0x06);

	if (auto ptr = util::pattern_scan(modules->engine, pattern("74 21 83 FE 04")))
		util::memset(ptr, 0x75, 0x01);

	if (auto ptr = util::pattern_scan(modules->engine, pattern("74 1E 83 FE 04")))
		util::memset(ptr, 0x90, 0x02);

	if (auto ptr = util::pattern_scan(modules->engine, pattern("74 1F 6A 04 8D 84 24 AC 01 00 00")))
		util::memset(ptr, 0xEB, 0x01);

	if (auto ptr = util::pattern_scan(modules->engine, pattern("75 26 50 51 68")))
		util::memset(ptr, 0xEB, 0x01);

	if (auto ptr = util::pattern_scan(modules->engine, pattern("7D 15 51 50 68")))
		util::memset(ptr, 0xEB, 0x01);

	if (auto ptr = util::pattern_scan(modules->engine, pattern("7E 15 51 50 68")))
		util::memset(ptr, 0xEB, 0x01);

	if (auto ptr = util::pattern_scan(modules->engine, patternm("74 37 A1 ? ? ? ? FF B0")))
		util::memset(ptr, 0x90, 0x02);
}

void c_patches::shutdown() {
	update_max_payload_bits(versions->get_local_bits());
}