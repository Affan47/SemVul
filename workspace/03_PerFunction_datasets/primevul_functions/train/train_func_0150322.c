preloadLibraries(void)
{
	void *vmDLL, *threadDLL, *portDLL;
	char* lastSep = 0;
	char* tempchar = 0;
	char* exeInBuf;
	J9StringBuffer * jvmDLLNameBuffer = NULL;
	char *lastDirName;
	char* vmDllName = J9_VM_DLL_NAME;
	struct stat statBuf;
#if defined(J9ZOS390)
	void *javaDLL;
#endif

#if defined(AIXPPC)
	size_t origLibpathLen = 0;
	const char *origLibpath = NULL;
#endif

	if (j9vm_dllHandle != 0) {
		return FALSE;
	}

#if defined(J9ZOS390)
	iconv_init();
#endif

#if defined(AIXPPC)
	origLibpath = getenv("LIBPATH");
	if (NULL != origLibpath) {
		origLibpathLen = strlen(origLibpath);
	}
#endif

	jvmDLLNameBuffer = getj9bin();
	j9binBuffer = jvmBufferCat(NULL, jvmBufferData(jvmDLLNameBuffer));

	addToLibpath(jvmBufferData(j9binBuffer), TRUE);


	lastDirName = strrchr(jvmBufferData(j9binBuffer), DIR_SEPARATOR);

	if (NULL == lastDirName) {
		fprintf(stderr, "Preload libraries failed to find a valid J9 binary location\n" );
		exit( -1 );
	}

	if (0 == strcmp(lastDirName + 1, "classic")) {
		truncatePath(jvmBufferData(j9binBuffer));
		truncatePath(jvmBufferData(j9binBuffer));
#if J9VM_JAVA9_BUILD < 150

		removeSuffix(jvmBufferData(j9binBuffer), "/lib");
#endif
		j9binBuffer = jvmBufferCat(j9binBuffer, J9VM_LIB_ARCH_DIR "j9vm/");
		if (-1 != stat(jvmBufferData(j9binBuffer), &statBuf)) {

			jvmDLLNameBuffer = jvmBufferCat(NULL, jvmBufferData(j9binBuffer));
		} else {

			free(j9binBuffer);
			j9binBuffer = NULL;
			j9binBuffer = jvmBufferCat(NULL, jvmBufferData(jvmDLLNameBuffer));
		}
	}


	jvmDLLNameBuffer = jvmBufferCat(jvmDLLNameBuffer, "/lib");
	jvmDLLNameBuffer = jvmBufferCat(jvmDLLNameBuffer, vmDllName);
	jvmDLLNameBuffer = jvmBufferCat(jvmDLLNameBuffer, J9PORT_LIBRARY_SUFFIX);

	if(-1 != stat (jvmBufferData(jvmDLLNameBuffer), &statBuf)) {
		jvmInSubdir = TRUE;
	} else {
		jvmInSubdir = FALSE;
	}

	DBG_MSG(("jvmInSubdir: %d\n", jvmInSubdir));

	free(jrebinBuffer);
	jrebinBuffer = NULL;


	if(jvmInSubdir) {
		jrebinBuffer = jvmBufferCat(NULL, jvmBufferData(j9binBuffer));
		truncatePath(jvmBufferData(jrebinBuffer));
	} else {
		truncatePath(jvmBufferData(j9binBuffer));
		jrebinBuffer = jvmBufferCat(NULL, jvmBufferData(j9binBuffer));
	}
	j9libBuffer = jvmBufferCat(NULL, jvmBufferData(jrebinBuffer));
#if !defined(OSX)


#if (J9VM_JAVA9_BUILD < 150)

	truncatePath(jvmBufferData(j9libBuffer));
#endif
#endif
	j9libvmBuffer = jvmBufferCat(NULL, jvmBufferData(j9binBuffer));
	j9Buffer = jvmBufferCat(NULL, jvmBufferData(jrebinBuffer));
	truncatePath(jvmBufferData(j9Buffer));

	DBG_MSG(("j9binBuffer   = <%s>\n", jvmBufferData(j9binBuffer)));
	DBG_MSG(("jrebinBuffer  = <%s>\n", jvmBufferData(jrebinBuffer)));
	DBG_MSG(("j9libBuffer   = <%s>\n", jvmBufferData(j9libBuffer)));
	DBG_MSG(("j9libvmBuffer = <%s>\n", jvmBufferData(j9libvmBuffer)));
	DBG_MSG(("j9Buffer      = <%s>\n", jvmBufferData(j9Buffer)));

	addToLibpath(jvmBufferData(jrebinBuffer), TRUE);

#if defined(AIXPPC)
	backupLibpath(&libpathBackup, origLibpathLen);
#endif

	omrsigDLL = preloadLibrary("omrsig", TRUE);
	if (NULL == omrsigDLL) {
		fprintf(stderr, "libomrsig failed to load: omrsig\n" );
		exit( -1 );
	}

	vmDLL = preloadLibrary(vmDllName, TRUE);
	if (NULL == vmDLL) {
		fprintf(stderr,"libjvm.so failed to load: %s\n", vmDllName);
		exit( -1 );
	}

	globalCreateVM = (CreateVM) dlsym (vmDLL, CREATE_JAVA_VM_ENTRYPOINT );
	globalGetVMs = (GetVMs) dlsym (vmDLL,  GET_JAVA_VMS_ENTRYPOINT);
	if ((NULL == globalCreateVM) || (NULL == globalGetVMs)) {
		dlclose(vmDLL);
		fprintf(stderr,"libjvm.so failed to load: global entrypoints not found\n");
		exit( -1 );
	}
	j9vm_dllHandle = vmDLL;

#ifdef J9ZOS390

	javaDLL = preloadLibrary("java", FALSE);
	if (!javaDLL) {
	   fprintf(stderr,"libjava.dll failed to load: %s\n", "java");
	   exit( -1 );
	}
	globalGetStringPlatform = (pGetStringPlatform) dlsym (javaDLL,  "IBMZOS_GetStringPlatform");
	globalGetStringPlatformLength = (pGetStringPlatformLength) dlsym (javaDLL,  "IBMZOS_GetStringPlatformLength");
	globalNewStringPlatform = (pNewStringPlatform) dlsym (javaDLL,  "IBMZOS_NewStringPlatform");
	global_a2e_vsprintf = (p_a2e_vsprintf) dlsym (javaDLL,  "IBMZOS_a2e_vsprintf");
	if (!globalGetStringPlatform || !globalGetStringPlatformLength || !globalNewStringPlatform || !global_a2e_vsprintf) {
	   dlclose(vmDLL);
	   dlclose(javaDLL);
	   fprintf(stderr,"libjava.dll failed to load: global entrypoints not found\n");
	   exit( -1 );
	}
	java_dllHandle = javaDLL;
#endif

	threadDLL = preloadLibrary(J9_THREAD_DLL_NAME, TRUE);
	f_threadGlobal = (ThreadGlobal) dlsym (threadDLL, "omrthread_global");
	f_threadAttachEx = (ThreadAttachEx) dlsym (threadDLL, "omrthread_attach_ex");
	f_threadDetach = (ThreadDetach) dlsym (threadDLL, "omrthread_detach");
	f_monitorEnter = (MonitorEnter) dlsym (threadDLL, "omrthread_monitor_enter");
	f_monitorExit = (MonitorExit) dlsym (threadDLL, "omrthread_monitor_exit");
	f_monitorInit = (MonitorInit) dlsym (threadDLL, "omrthread_monitor_init_with_name");
	f_monitorDestroy = (MonitorDestroy) dlsym (threadDLL, "omrthread_monitor_destroy");
	f_monitorWaitTimed = (MonitorWaitTimed) dlsym (threadDLL, "omrthread_monitor_wait_timed");
	f_monitorNotify = (MonitorNotify) dlsym (threadDLL, "omrthread_monitor_notify");
	f_monitorNotifyAll = (MonitorNotifyAll) dlsym (threadDLL, "omrthread_monitor_notify_all");
	f_threadLibControl = (ThreadLibControl) dlsym (threadDLL, "omrthread_lib_control");
	f_setCategory = (SetCategory) dlsym (threadDLL, "omrthread_set_category");
	f_libEnableCPUMonitor = (LibEnableCPUMonitor) dlsym (threadDLL, "omrthread_lib_enable_cpu_monitor");
	if (!f_threadGlobal || !f_threadAttachEx || !f_threadDetach || !f_monitorEnter || !f_monitorExit || !f_monitorInit || !f_monitorDestroy || !f_monitorWaitTimed
		|| !f_monitorNotify || !f_monitorNotifyAll || !f_threadLibControl || !f_setCategory || !f_libEnableCPUMonitor) {
		dlclose(vmDLL);
#ifdef J9ZOS390
		dlclose(javaDLL);
#endif
		dlclose(threadDLL);
		fprintf(stderr,"libjvm.so failed to load: thread library entrypoints not found\n");
		exit( -1 );
	}
	portDLL = preloadLibrary(J9_PORT_DLL_NAME, TRUE);
	portInitLibrary = (PortInitLibrary) dlsym (portDLL, "j9port_init_library");
	portGetSizeFn = (PortGetSize) dlsym (portDLL, "j9port_getSize");
	portGetVersionFn = (PortGetVersion) dlsym (portDLL, "j9port_getVersion");
	if (!portInitLibrary) {
		dlclose(vmDLL);
#ifdef J9ZOS390
		dlclose(javaDLL);
#endif
		dlclose(threadDLL);
		dlclose(portDLL);
		fprintf(stderr,"libjvm.so failed to load: %s entrypoints not found\n", J9_PORT_DLL_NAME);
		exit( -1 );
	}

#ifdef J9_CLEAR_VM_INTERFACE_DLL_NAME


	preloadLibrary(J9_CLEAR_VM_INTERFACE_DLL_NAME, TRUE);
#endif

#ifdef J9VM_OPT_HARMONY


	preloadLibrary(J9_HARMONY_PORT_LIBRARY_SHIM_DLL_NAME, TRUE);
#endif
	return TRUE;
}
