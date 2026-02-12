BOOL APIENTRY DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	BOOL rcDllMain = TRUE;
	jvm_dllHandle = hModule;

	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {

		DisableThreadLibraryCalls(hModule);
	}

	return rcDllMain;
}
