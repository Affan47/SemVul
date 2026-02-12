preloadLibraries(void)
{
	char* tempchar = 0;
	char jvmDLLName[J9_MAX_PATH];
	J9StringBuffer * jvmDLLNameBuffer = NULL;
	wchar_t unicodeDLLName[J9_MAX_PATH + 1] = {0};
	DWORD unicodeDLLNameLength = 0;
	UINT prevMode;
	HINSTANCE vmDLL = 0;
	HINSTANCE threadDLL = 0;
	HINSTANCE portDLL = 0;
	char* vmDllName = J9_VM_DLL_NAME;
	char* vmName = NULL;
	static beenRun=FALSE;
	if(beenRun) {
		return TRUE;
	}
	beenRun = TRUE;

	unicodeDLLNameLength = GetModuleFileNameW(jvm_dllHandle, unicodeDLLName, (J9_MAX_PATH + 1));

	if (unicodeDLLNameLength > (DWORD)J9_MAX_PATH) {
		fprintf(stderr,"ERROR: failed to load library. Path is too long: %ls\n", unicodeDLLName);
		return FALSE;
	}


	WideCharToMultiByte(OS_ENCODING_CODE_PAGE, OS_ENCODING_WC_FLAGS, unicodeDLLName, -1,  jvmDLLName, J9_MAX_PATH, NULL, NULL);

	jvmDLLNameBuffer = jvmBufferCat(NULL, jvmDLLName);
	j9binBuffer = jvmBufferCat(j9binBuffer, jvmDLLName);


	truncatePath(jvmBufferData(jvmDLLNameBuffer));
	jvmDLLNameBuffer = jvmBufferCat(jvmDLLNameBuffer, "\\");
	jvmDLLNameBuffer = jvmBufferCat(jvmDLLNameBuffer, vmDllName);
	jvmDLLNameBuffer = jvmBufferCat(jvmDLLNameBuffer, ".dll");


	MultiByteToWideChar(OS_ENCODING_CODE_PAGE, OS_ENCODING_MB_FLAGS, jvmBufferData(jvmDLLNameBuffer), -1, unicodeDLLName, J9_MAX_PATH);
	if(INVALID_FILE_ATTRIBUTES != GetFileAttributesW(unicodeDLLName)) {
		jvmInSubdir = TRUE;
	} else {
		jvmInSubdir = FALSE;
	}

	prevMode = SetErrorMode( SEM_NOOPENFILEERRORBOX|SEM_FAILCRITICALERRORS );

	free(jvmDLLNameBuffer);
	jvmDLLNameBuffer = NULL;
	free(jrebinBuffer);
	jrebinBuffer = NULL;

	if(jvmInSubdir) {

		truncatePath(jvmBufferData(j9binBuffer));
		jrebinBuffer = jvmBufferCat(NULL, jvmBufferData(j9binBuffer));
		truncatePath(jvmBufferData(jrebinBuffer));
	} else {

		truncatePath(jvmBufferData(j9binBuffer));
		truncatePath(jvmBufferData(j9binBuffer));
		jrebinBuffer = jvmBufferCat(NULL, jvmBufferData(j9binBuffer));
	}

	j9libBuffer = jvmBufferCat(NULL, jvmBufferData(jrebinBuffer));
	truncatePath(jvmBufferData(j9libBuffer));
	j9Buffer = jvmBufferCat(NULL, jvmBufferData(j9libBuffer));
	truncatePath(jvmBufferData(j9Buffer));
	j9libBuffer = jvmBufferCat(j9libBuffer, DIR_SEPARATOR_STR "lib");

	j9libvmBuffer = jvmBufferCat(NULL, jvmBufferData(j9libBuffer));

	vmName = strrchr(jvmBufferData(j9binBuffer), DIR_SEPARATOR);
	if (NULL != vmName) {
		j9libvmBuffer = jvmBufferCat(j9libvmBuffer, vmName);
	}

	DBG_MSG(("j9binBuffer   = <%s>\n", jvmBufferData(j9binBuffer)));
	DBG_MSG(("jrebinBuffer  = <%s>\n", jvmBufferData(jrebinBuffer)));
	DBG_MSG(("j9libBuffer   = <%s>\n", jvmBufferData(j9libBuffer)));
	DBG_MSG(("j9libvmBuffer = <%s>\n", jvmBufferData(j9libvmBuffer)));
	DBG_MSG(("j9Buffer      = <%s>\n", jvmBufferData(j9Buffer)));

#if !CALL_BUNDLED_FUNCTIONS_DIRECTLY
	vmDLL = (HINSTANCE) preloadLibrary(vmDllName, TRUE);
	preloadLibrary(J9_HOOKABLE_DLL_NAME, TRUE);

	SetErrorMode( prevMode );

	if (vmDLL < (HINSTANCE)HINSTANCE_ERROR) {
		fprintf(stderr,"jvm.dll failed to load: %s\n", vmDllName);
		return FALSE;
	}
	globalCreateVM = (CreateVM) GetProcAddress (vmDLL, (LPCSTR) CREATE_JAVA_VM_ENTRYPOINT );
	globalGetVMs = (GetVMs) GetProcAddress (vmDLL, (LPCSTR) GET_JAVA_VMS_ENTRYPOINT);
	if (!globalCreateVM || !globalGetVMs) {
		FreeLibrary(vmDLL);
		fprintf(stderr,"jvm.dll failed to load: global entrypoints not found\n");
		return FALSE;
	}
	j9vm_dllHandle = vmDLL;

	threadDLL = (HINSTANCE) preloadLibrary(J9_THREAD_DLL_NAME, TRUE);
	f_threadGlobal = (ThreadGlobal) GetProcAddress (threadDLL, (LPCSTR) "omrthread_global");
	f_threadAttachEx = (ThreadAttachEx) GetProcAddress (threadDLL, (LPCSTR) "omrthread_attach_ex");
	f_threadDetach = (ThreadDetach) GetProcAddress (threadDLL, (LPCSTR) "omrthread_detach");
	f_monitorEnter = (MonitorEnter) GetProcAddress (threadDLL, (LPCSTR) "omrthread_monitor_enter");
	f_monitorExit = (MonitorExit) GetProcAddress (threadDLL, (LPCSTR) "omrthread_monitor_exit");
	f_monitorInit = (MonitorInit) GetProcAddress (threadDLL, (LPCSTR) "omrthread_monitor_init_with_name");
	f_monitorDestroy = (MonitorDestroy) GetProcAddress (threadDLL, (LPCSTR) "omrthread_monitor_destroy");
	f_monitorWaitTimed = (MonitorWaitTimed) GetProcAddress (threadDLL, (LPCSTR) "omrthread_monitor_wait_timed");
	f_monitorNotify = (MonitorNotify) GetProcAddress (threadDLL, (LPCSTR) "omrthread_monitor_notify");
	f_monitorNotifyAll = (MonitorNotifyAll) GetProcAddress (threadDLL, (LPCSTR) "omrthread_monitor_notify_all");
	f_threadLibControl = (ThreadLibControl) GetProcAddress (threadDLL, (LPCSTR) "omrthread_lib_control");
	f_setCategory = (SetCategory) GetProcAddress (threadDLL, (LPCSTR) "omrthread_set_category");
	f_libEnableCPUMonitor = (LibEnableCPUMonitor) GetProcAddress (threadDLL, (LPCSTR) "omrthread_lib_enable_cpu_monitor");
	if (!f_threadGlobal || !f_threadAttachEx || !f_threadDetach || !f_monitorEnter || !f_monitorExit || !f_monitorInit || !f_monitorDestroy || !f_monitorWaitTimed
		|| !f_monitorNotify || !f_monitorNotifyAll || !f_threadLibControl || !f_setCategory || !f_libEnableCPUMonitor) {
		FreeLibrary(vmDLL);
		FreeLibrary(threadDLL);
		fprintf(stderr,"jvm.dll failed to load: thread library entrypoints not found\n");
		return FALSE;
	}


	portDLL = (HINSTANCE) preloadLibrary(J9_PORT_DLL_NAME, TRUE);
	portInitLibrary = (PortInitLibrary) GetProcAddress (portDLL, (LPCSTR) "j9port_init_library");
	portGetSizeFn = (PortGetSize) GetProcAddress (portDLL, (LPCSTR) "j9port_getSize");
	portGetVersionFn = (PortGetVersion) GetProcAddress (portDLL, (LPCSTR) "j9port_getVersion");
	if (!portInitLibrary) {
		FreeLibrary(vmDLL);
		FreeLibrary(threadDLL);
		FreeLibrary(portDLL);
		fprintf(stderr,"jvm.dll failed to load: %s entrypoints not found\n", J9_PORT_DLL_NAME);
		return FALSE;
	}
	preloadLibrary(J9_ZIP_DLL_NAME, TRUE);

#ifdef J9_CLEAR_VM_INTERFACE_DLL_NAME


	preloadLibrary(J9_CLEAR_VM_INTERFACE_DLL_NAME, TRUE);
#endif

#endif


#ifdef J9VM_OPT_HARMONY
	preloadLibrary(J9_HARMONY_PORT_LIBRARY_SHIM_DLL_NAME, TRUE);
#endif
	return TRUE;
}
