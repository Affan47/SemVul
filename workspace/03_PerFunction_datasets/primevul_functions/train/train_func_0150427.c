JVM_Write(jint descriptor, const char* buffer, jint length)
{
	PORT_ACCESS_FROM_JAVAVM(BFUjavaVM);
	jint result = 0;

	Trc_SC_Write_Entry(descriptor, buffer, length);

	if (descriptor == -1) {
		Trc_SC_Write_bad_descriptor();
		return JVM_IO_ERR;
	}

#ifndef J9ZOS390


	if ( (descriptor == 1) || (descriptor == 2) ) {
		IDATA retval = j9file_write(descriptor, (char *)buffer, length);
		if(retval<0) {
			result = -1;
		} else {
			result = (jint)retval;
			Assert_SC_true(retval == (IDATA)result);
		}
	} else
#endif
	{

		do {
			result = write(descriptor, buffer, length);
		} while ((-1 == result) && (EINTR == errno));
	}

	Trc_SC_Write_Exit(result);

	return result;
}
