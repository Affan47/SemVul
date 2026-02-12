JVM_LoadLibrary(const char *libName)
{
	JNIEnv *env;
	JavaVM *vm = (JavaVM *) BFUjavaVM;
	char errMsg[512];

#ifdef WIN32
	HINSTANCE dllHandle;
	UINT prevMode;

	Trc_SC_LoadLibrary_Entry(libName);

	prevMode = SetErrorMode( SEM_NOOPENFILEERRORBOX|SEM_FAILCRITICALERRORS );


	dllHandle = LoadLibrary ((LPCSTR)libName);
	if (NULL == dllHandle) {
		goto _end;
	}

	SetErrorMode(prevMode);
	Trc_SC_LoadLibrary_Exit(dllHandle);
	return dllHandle;

_end:
	SetErrorMode(prevMode);

#endif

#if defined(J9UNIX) || defined(J9ZOS390)
	void *dllHandle;
#if defined(AIXPPC)


	loadAndInit((char *)libName, L_RTLD_LOCAL, NULL);
#endif
	dllHandle = dlopen( (char *)libName, RTLD_LAZY );
	if(NULL != dllHandle) {
		Trc_SC_LoadLibrary_Exit(dllHandle);
		return dllHandle;
	}
#endif


 	(*vm)->GetEnv(vm, (void **) &env, JNI_VERSION_1_2);
 	if (NULL != env) {
 		j9portLibrary.omrPortLibrary.str_printf(&j9portLibrary.omrPortLibrary, errMsg, sizeof(errMsg), "Failed to load library \"%s\"", libName);
 		throwNewUnsatisfiedLinkError(env, errMsg);
 	}

	Trc_SC_LoadLibrary_Exit(NULL);
	return NULL;
}
