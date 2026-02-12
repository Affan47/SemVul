JNI_GetCreatedJavaVMs(JavaVM **vmBuf, jsize bufLen, jsize *nVMs)
{
	jint result;
	Trc_SC_GetCreatedJavaVMs_Entry(vmBuf, bufLen, nVMs);


	if(librariesLoaded()){
#if CALL_BUNDLED_FUNCTIONS_DIRECTLY
		result = J9_GetCreatedJavaVMs(vmBuf, bufLen, nVMs);
#else
		result = globalGetVMs(vmBuf, bufLen, nVMs);
#endif
	} else {

		result = JNI_OK;
		*nVMs = 0;
	}

	Trc_SC_GetCreatedJavaVMs_Exit(result, *nVMs);
	return result;
}
