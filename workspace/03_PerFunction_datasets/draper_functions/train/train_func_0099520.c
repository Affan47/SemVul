_db_print(const char *format,...)
{
#else
_db_print(va_alist)
     va_dcl
{
    const char *format = NULL;
#endif
    LOCAL_ARRAY(char, f, BUFSIZ);
    va_list args1;
#if STDC_HEADERS
    va_list args2;
    va_list args3;
#else
#define args2 args1
#define args3 args1
#endif
#ifdef _SQUID_MSWIN_

    if (!dbg_mutex) {
	HMODULE krnl_lib = GetModuleHandle("Kernel32");
	BOOL(FAR WINAPI * InitializeCriticalSectionAndSpinCount)
	    (LPCRITICAL_SECTION, DWORD) = NULL;
	if (krnl_lib)
	    InitializeCriticalSectionAndSpinCount =
		GetProcAddress(krnl_lib,
		"InitializeCriticalSectionAndSpinCount");
	dbg_mutex = xcalloc(1, sizeof(CRITICAL_SECTION));

	if (InitializeCriticalSectionAndSpinCount) {

	    if (!InitializeCriticalSectionAndSpinCount(dbg_mutex, 4000)) {
		if (debug_log) {
		    fprintf(debug_log, "FATAL: _db_print: can't initialize critical section\n");
		    fflush(debug_log);
		}
		fprintf(stderr, "FATAL: _db_print: can't initialize critical section\n");
		abort();
	    } else
		InitializeCriticalSection(dbg_mutex);
	}
    }
    EnterCriticalSection(dbg_mutex);
#endif

    if (!Ctx_Lock)
	ctx_print();
#if STDC_HEADERS
    va_start(args1, format);
    va_start(args2, format);
    va_start(args3, format);
#else
    format = va_arg(args1, const char *);
#endif
    snprintf(f, BUFSIZ, "%s| %s",
	debugLogTime(squid_curtime),
	format);
    _db_print_file(f, args1);
    _db_print_stderr(f, args2);
#if HAVE_SYSLOG
    _db_print_syslog(format, args3);
#endif
#ifdef _SQUID_MSWIN_
    LeaveCriticalSection(dbg_mutex);
#endif
    va_end(args1);
#if STDC_HEADERS
    va_end(args2);
    va_end(args3);
#endif
}
