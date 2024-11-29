#include <proxy.h>

class c_plugin {
public:
	c_plugin() = default;
	virtual bool load(void* interface_factory, void* game_server_factory) { return true; }
	virtual void unload(void) { proxy->shutdown(); }
	virtual void pause(void) {}
	virtual void unpause(void) {}
	virtual const char* get_plugin_description(void) { return "not a proxy"; }
	virtual void level_init(void*) {}
	virtual void server_activate(void*, void*, void*) {}
	virtual void game_frame(bool) {}
	virtual void level_shutdown(void) {}
	virtual void client_active(void*) {}
	virtual void client_fully_connect(void*) {}
	virtual void client_disconnect(void*) {}
	virtual void client_put_in_server(void*, void*) {}
	virtual void set_command_client(void*) {}
	virtual void client_settings_changed(void*) {}
	virtual int client_connect(void*, void*, void*, void*, void*, void*) { return 0; }
	virtual int client_command(void*, void*) { return 0; }
	virtual void network_id_validated(void*, void*) {}
} plugin;

extern "C"  __declspec(dllexport) c_plugin* __cdecl CreateInterface(const char* name, int32_t* ret) {
	if (!strcmp(name, "ISERVERPLUGINCALLBACKS001")) {
		if (ret)
			*ret = 0;

		return &plugin;
	}

	if (ret)
		*ret = 1;

	return NULL;
}