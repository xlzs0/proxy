#pragma once

#include <common.h>

class c_patches {
public:
    void update_max_payload_bits(uint8_t new_bits = 0);
    void initialize();
    void shutdown();
};

inline std::unique_ptr<c_patches> patches = std::make_unique<c_patches>();