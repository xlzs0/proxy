#include <addresses.h>
#include <bytes.h>
#include <hooks.h>
#include <interfaces.h>
#include <messages.h>
#include <patches.h>
#include <versions.h>

#include <google/protobuf/message_lite.h>
#include <google/protobuf/io/coded_stream.h>
#include <safetyhook/safetyhook.hpp>

struct c_net_msg {
	int get_type() {
		return util::call_this<int>(this, 7);
	}

	int get_group() {
		return util::call_this<int>(this, 8);
	}

	template<typename ret>
	__forceinline ret* get() {
		return reinterpret_cast<ret*>(reinterpret_cast<uintptr_t>(this) + 0x04);
	}
};

namespace originals {
	SafetyHookInline send_net_msg;
	SafetyHookInline class_info;
	SafetyHookInline send_table;
	SafetyHookInline clamp_bones_in_bbox;
	SafetyHookInline get_channel_encryption_key;
	SafetyHookInline process_connectionless_packet;
}

namespace targets {
	__forceinline void update_clamp_bones_in_bbox() {
		if (!addresses->clamp_bones_in_bbox)
			return;

		bool enabled = originals::clamp_bones_in_bbox.enabled();
		if (versions->server == versions->target) {
			if (!enabled)
				originals::clamp_bones_in_bbox.enable();

			return;
		}

		if (enabled)
			originals::clamp_bones_in_bbox.disable();
	}

	__forceinline void parse_table(const uint8_t* table_ptr, const size_t& size) {
		google::protobuf::io::CodedInputStream coded_table(table_ptr, size);
		CSVCMsg_SendTable send_table;
		if (send_table.ParseFromCodedStream(&coded_table))
			originals::send_table.unsafe_stdcall<bool>(&send_table);
	}

	__forceinline void parse_classes(const uint8_t* send_info, const size_t& size) {
		google::protobuf::io::CodedInputStream coded_send_info(send_info, size);
		CSVCMsg_ClassInfo info;
		if (info.ParseFromCodedStream(&coded_send_info))
			originals::class_info.unsafe_thiscall<int>(reinterpret_cast<uintptr_t>(interfaces->client_state) + 0x08, &info);
	}

	void __stdcall clamp_bones_in_bbox(int, int) {}

	bool __fastcall send_net_msg(int a1, int, c_net_msg* msg, bool a4, bool a5) {
		const auto msg_type = msg->get_type();
		if (msg_type == 14)
			return true;

		if (versions->server == versions->target) {
			if (msg_type == 8)
				msg->get<CCLCMsg_ClientInfo>()->set_send_table_crc(0xAEAF7AB8);

			if (msg_type == 9)
				messages->fix_move_cmd(msg->get<CCLCMsg_Move>());
		}

		return originals::send_net_msg.unsafe_thiscall<bool>(a1, msg, a4, a5);
	}

	bool __fastcall class_info(int a1, int, CSVCMsg_ClassInfo* a3) {
		if (versions->server != versions->target)
			return originals::class_info.unsafe_thiscall<bool>(a1, a3);

		for (size_t i = 0; i < byte_arrays::table_offsets.size() - 1; i++) {
			size_t start = byte_arrays::table_offsets[i];
			size_t end = byte_arrays::table_offsets[i + 1];

			parse_table(byte_arrays::table_bytes.data() + start, end - start);
		}

		parse_classes(byte_arrays::classes_bytes.data(), byte_arrays::classes_bytes.size());

		return true;
	}

	bool __stdcall send_table(CSVCMsg_SendTable* send_table) {
		if (versions->server != versions->target)
			return originals::send_table.unsafe_stdcall<bool>(send_table);

		return true;
	}

	uint32_t last_host_version;
	uint8_t default_encryption_key[16]{};

	uint8_t* __fastcall get_channel_encryption_key(int* _this) {
		auto host_version = versions->server;

		if (last_host_version != host_version) {
			last_host_version = host_version;

			uint8_t new_key[] = {
				'C', 'S', 'G', 'O',

				static_cast<uint8_t>((host_version >> 0x00) & 0xFF), static_cast<uint8_t>((host_version >> 0x08) & 0xFF),
				static_cast<uint8_t>((host_version >> 0x10) & 0xFF), static_cast<uint8_t>((host_version >> 0x18) & 0xFF),

				static_cast<uint8_t>((host_version >> 0x02) & 0xFF), static_cast<uint8_t>((host_version >> 0x0A) & 0xFF),
				static_cast<uint8_t>((host_version >> 0x12) & 0xFF), static_cast<uint8_t>((host_version >> 0x1A) & 0xFF),

				static_cast<uint8_t>((host_version >> 0x04) & 0xFF), static_cast<uint8_t>((host_version >> 0x0C) & 0xFF),
				static_cast<uint8_t>((host_version >> 0x14) & 0xFF), static_cast<uint8_t>((host_version >> 0x1C) & 0xFF),
			};

			memcpy(reinterpret_cast<void*>(default_encryption_key), new_key, sizeof(new_key));
		}

		if (_this[0x106E])
			return reinterpret_cast<uint8_t*>(_this[0x106D]);

		return default_encryption_key;
	}


	bool __fastcall process_connectionless_packet(int _this, int, int a2) {
		auto ret = originals::process_connectionless_packet.unsafe_thiscall<bool>(_this, a2);

		if (auto version = interfaces->client_state->server_version(); version > 0)
			versions->server = version;

		patches->update_max_payload_bits();
		update_clamp_bones_in_bbox();

		return ret;
	}
}

void c_hooks::initialize() {
	originals::send_net_msg = safetyhook::create_inline(addresses->send_net_msg, targets::send_net_msg);
	originals::send_table = safetyhook::create_inline(addresses->send_table, targets::send_table);
	originals::class_info = safetyhook::create_inline(addresses->class_info, targets::class_info);

	if (addresses->clamp_bones_in_bbox)
		originals::clamp_bones_in_bbox = safetyhook::create_inline(addresses->clamp_bones_in_bbox, targets::clamp_bones_in_bbox);

	originals::get_channel_encryption_key = safetyhook::create_inline(addresses->get_channel_encryption_key, targets::get_channel_encryption_key);
	originals::process_connectionless_packet = safetyhook::create_inline(addresses->process_connectionless_packet, targets::process_connectionless_packet);
}

void c_hooks::shutdown() {
	originals::send_net_msg.reset();
	originals::send_table.reset();
	originals::class_info.reset();
	originals::clamp_bones_in_bbox.reset();
	originals::get_channel_encryption_key.reset();
	originals::process_connectionless_packet.reset();
}