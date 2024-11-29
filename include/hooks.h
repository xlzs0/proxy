#pragma once

class c_hooks {
public:
	void initialize();
	void shutdown();
};

inline std::unique_ptr<c_hooks> hooks = std::make_unique<c_hooks>();