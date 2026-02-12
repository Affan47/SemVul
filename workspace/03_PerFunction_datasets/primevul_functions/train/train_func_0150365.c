isSignalReservedByJVM(jint sigNum)
{
	return
#if defined(SIGFPE)
		(SIGFPE == sigNum) ||
#endif
#if defined(SIGILL)
		(SIGILL == sigNum) ||
#endif
#if defined(SIGSEGV)
		(SIGSEGV == sigNum) ||
#endif
#if defined(SIGBUS)
		(SIGBUS == sigNum) ||
#endif
#if defined(SIGTRAP)
		(SIGTRAP == sigNum) ||
#endif
#if defined(SIGQUIT)
		(SIGQUIT == sigNum) ||
#endif
#if defined(SIGBREAK)
		(SIGBREAK == sigNum) ||
#endif
#if defined(SIGABRT)
		(SIGABRT == sigNum) ||
#endif
#if defined(SIGCHLD)
		(SIGCHLD == sigNum) ||
#endif
#if defined(SIGRECONFIG)
		(SIGRECONFIG == sigNum) ||
#endif
#if defined(J9ZOS390) && defined(SIGUSR1)
		(SIGUSR1 == sigNum) ||
#endif
		FALSE;
}
