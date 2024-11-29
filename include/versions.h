#pragma once

#include <common.h>

class c_versions {
	__forceinline auto get_max_payload_bits(uint32_t protocol_version) const {
		if (protocol_version >= 13881)
			return 20;

		if (protocol_version >= 13731)
			return 19;

		return 18;
	}
public:
	uint32_t local;
	uint32_t target;
	uint32_t server;

	__forceinline const auto get_local_bits() const {
		return get_max_payload_bits(this->local);
	}

	__forceinline const auto get_target_bits() const {
		return get_max_payload_bits(this->target);
	}

	__forceinline const auto get_server_bits() const {
		return get_max_payload_bits(this->server);
	}
};

inline std::unique_ptr<c_versions> versions = std::make_unique<c_versions>();