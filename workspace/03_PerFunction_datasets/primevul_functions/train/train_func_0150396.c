JVM_Read(jint descriptor, char *buffer, jint bytesToRead)
{
	PORT_ACCESS_FROM_JAVAVM(BFUjavaVM);
	jint result = 0;

	Trc_SC_Read_Entry(descriptor, buffer, bytesToRead);

	if (descriptor == -1) {
		Trc_SC_Read_bad_descriptor();
		return -1;
	}

#ifndef J9ZOS390


	if (descriptor == 0) {
		IDATA charsRead = j9tty_get_chars(buffer, bytesToRead);
		result = (jint)charsRead;
		Assert_SC_true(charsRead == (IDATA)result);
	} else
#endif
	{

		do {
			result = read(descriptor, buffer, bytesToRead);
		} while ((-1 == result) && (EINTR == errno));
	}

	Trc_SC_Read_Exit(result, errno);

	return result;
}
