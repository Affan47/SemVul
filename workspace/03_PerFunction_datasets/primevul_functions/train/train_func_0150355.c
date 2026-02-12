JVM_Send(jint descriptor, const char* buffer, jint numBytes, jint flags)
{
	jint retVal;

	Trc_SC_Send_Entry(descriptor, buffer, numBytes, flags);

#if defined (WIN32)
	retVal = send(descriptor, buffer, numBytes, flags);
#else
	do {
		retVal = send(descriptor, buffer, numBytes, flags);
	} while ((-1 == retVal) && (EINTR == errno));
#endif

	Trc_SC_Send_Exit(retVal);

	return retVal;
}
