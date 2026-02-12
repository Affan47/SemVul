isSignalUsedForShutdown(jint sigNum)
{
	return
#if defined(SIGHUP)
		(SIGHUP == sigNum) ||
#endif
#if defined(SIGINT)
		(SIGINT == sigNum) ||
#endif
#if defined(SIGTERM)
		(SIGTERM == sigNum) ||
#endif
		FALSE;
}
