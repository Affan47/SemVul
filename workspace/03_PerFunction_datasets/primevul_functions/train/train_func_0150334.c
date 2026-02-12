JVM_Close(jint descriptor)
{
	jint result = 0;

	Trc_SC_Close_Entry(descriptor);

	if (descriptor == -1) {
		Trc_SC_Close_bad_descriptor();
		return JVM_IO_ERR;
	}


	if (descriptor >= 0 && descriptor <= 2) {
		Trc_SC_Close_std_descriptor();
		return 0;
	}

	result = close(descriptor);

	Trc_SC_Close_Exit(result);

	return result;
}
