JVM_Lseek(jint descriptor, jlong bytesToSeek, jint origin)
{
	jlong result = 0;
#if defined (LINUX)
	loff_t longResult = 0;
#endif

	Trc_SC_Lseek_Entry(descriptor, bytesToSeek, origin);

	if (descriptor == -1) {
		Trc_SC_Lseek_bad_descriptor();
		return JVM_IO_ERR;
	}

#if defined(WIN32)
#ifdef __IBMC__
	result = lseek(descriptor, (long) bytesToSeek, origin);
#else
	result = _lseeki64(descriptor, bytesToSeek, origin);
#endif
#elif defined(J9UNIX) || defined(J9ZOS390)
#if defined(LINUX) && !defined(J9VM_ENV_DATA64)

#if __GLIBC_PREREQ(2,4)

	result = lseek64(descriptor, bytesToSeek, origin);
#else

	result = _llseek(descriptor, (unsigned long) ((bytesToSeek >> 32) & 0xFFFFFFFF), (unsigned long) (bytesToSeek & 0xFFFFFFFF), &longResult, origin);
	if (0 == result) {

		result = (jlong) longResult;
	}
#endif

#else
	result = lseek(descriptor, (off_t) bytesToSeek, origin);
#endif
#else
#error No JVM_Lseek provided
#endif

	Trc_SC_Lseek_Exit(result);

	return result;
}
