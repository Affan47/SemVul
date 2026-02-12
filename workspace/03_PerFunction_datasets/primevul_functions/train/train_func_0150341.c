JVM_RaiseSignal(jint sigNum)
{
	jboolean rc = JNI_FALSE;
	J9JavaVM *javaVM = (J9JavaVM *)BFUjavaVM;
	BOOLEAN isShutdownSignal = isSignalUsedForShutdown(sigNum);
	BOOLEAN isSignalIgnored = FALSE;
	int32_t isSignalIgnoredError = 0;
	uint32_t portlibSignalFlag = 0;

	PORT_ACCESS_FROM_JAVAVM(javaVM);

	Trc_SC_RaiseSignal_Entry(sigNum);

	portlibSignalFlag = j9sig_map_os_signal_to_portlib_signal(sigNum);
	if (0 != portlibSignalFlag) {
		isSignalIgnoredError = j9sig_is_signal_ignored(portlibSignalFlag, &isSignalIgnored);
	}

	if (isSignalReservedByJVM(sigNum)) {


	} else if (J9_ARE_ALL_BITS_SET(javaVM->sigFlags, J9_SIG_XRS_ASYNC) && isShutdownSignal) {


	} else if (isShutdownSignal && ((0 == isSignalIgnoredError) && isSignalIgnored)) {

	} else {
		raise(sigNum);
		rc = JNI_TRUE;
	}

	Trc_SC_RaiseSignal_Exit(rc);

	return rc;
}
