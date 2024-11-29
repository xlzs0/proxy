#include <addresses.h>
#include <hooks.h>
#include <interfaces.h>
#include <patches.h>
#include <proxy.h>
#include <versions.h>

DWORD WINAPI c_proxy::init_thread(void*) {
	while (!shadow::dll("serverbrowser").raw())
		SleepEx(200, FALSE);

	versions->target = 13731;
	modules->initialize();
	addresses->initialize();
	interfaces->initialize();
	patches->initialize();
	hooks->initialize();

	auto local_version = interfaces->client_state->server_version();
	if (addresses->protocol_version)
		local_version = **reinterpret_cast<uint32_t**>(addresses->protocol_version + 1);

	versions->local = local_version;

	return NULL;
}

void c_proxy::initialize() {
	CreateThread(NULL, NULL, this->init_thread, NULL, NULL, NULL);
}

void c_proxy::shutdown() {
	patches->shutdown();
	hooks->shutdown();
}