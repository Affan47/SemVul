JVM_FindSignal(const char *sigName)
{
	const J9SignalMapping *mapping = NULL;
	jint signalValue = J9_SIG_ERR;
	BOOLEAN nameHasSigPrefix = FALSE;
	const char *fullSigName = sigName;
#if !defined(WIN32)
	char nameWithSIGPrefix[J9_SIGNAME_BUFFER_LENGTH] = {0};
#endif

	Trc_SC_FindSignal_Entry(sigName);

	if (NULL != sigName) {
		size_t sigPrefixLength = sizeof(J9_SIG_PREFIX) - 1;

#if !defined(WIN32)
		if (0 != strncmp(sigName, J9_SIG_PREFIX, sigPrefixLength)) {


			size_t sigNameLength = sigPrefixLength + strlen(sigName) + 1;
			if (sigNameLength <= J9_SIGNAME_BUFFER_LENGTH) {
				strcpy(nameWithSIGPrefix, J9_SIG_PREFIX);
				strcat(nameWithSIGPrefix, sigName);
				fullSigName = nameWithSIGPrefix;
			} else {
				goto exit;
			}
		}
#endif

		for (mapping = signalMap; NULL != mapping->signalName; mapping++) {
			if (0 == strcmp(fullSigName, mapping->signalName)) {
				signalValue = mapping->signalValue;
				break;
			}
		}
	}

#if !defined(WIN32)
exit:
#endif
	Trc_SC_FindSignal_Exit(signalValue);
	return signalValue;
}
