JVM_FindLibraryEntry(void* handle, const char *functionName)
{
	void* result;

	Trc_SC_FindLibraryEntry_Entry(handle, functionName);

#if defined(WIN32)
	result = GetProcAddress ((HINSTANCE)handle, (LPCSTR)functionName);
#elif defined(J9UNIX) || defined(J9ZOS390)
	result = (void*)dlsym( (void*)handle, (char *)functionName );
#else
#error "Please implemente jvm.c:JVM_FindLibraryEntry(void* handle, const char *functionName)"
#endif

	Trc_SC_FindLibraryEntry_Exit(result);

	return result;
}
