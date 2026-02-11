variable_writes_src(
	struct rc_variable * var,
	unsigned int src_type,
	void * src)
{
	unsigned int i;
	for (i = 0; i < var->ReaderCount; i++) {
		if (reader_equals_src(var->Readers[i], src_type, src)) {
			return 1;
		}
	}
	return 0;
}
