#include <proxy.h>

BOOL WINAPI DllMain(HINSTANCE base, DWORD reason, LPVOID reserved) {
	if (reason == DLL_PROCESS_ATTACH)
		proxy->initialize();

	return TRUE;
}