static int is_seq(unsigned char * seq, unsigned int *seq_size, unsigned int *seq_len)
{
	int i,j,k;

	if (seq[0] != 0x30)
		return 0;
	if (seq[1] & 0x80) {
		i = seq[1] & 0x7f;
		if (i > 2 || i == 0)
			return 0;
		if (seq[2] == 0)
			return 0;
		k = 0;
		for (j = 0; j < i; j++) {
			k = (k << 8) + seq[j + 2];
		}
		if (k < 128)
			return 0;
	} else {
		  i = 0;
		  k = seq[1];
	}

	*seq_size = i + 2;
	*seq_len = k;
	return 1;
}
