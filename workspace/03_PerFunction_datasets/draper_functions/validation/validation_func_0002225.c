inx2bitfmt (int *inx)
{
	int j=0;
	char *bit_char_ptr = NULL;

	if (inx == NULL)
		return NULL;

	while (inx[j] >= 0) {
		if(bit_char_ptr)
			xstrfmtcat(bit_char_ptr, ",%d-%d", inx[j], inx[j+1]);
		else
			xstrfmtcat(bit_char_ptr, "%d-%d", inx[j], inx[j+1]);
		j += 2;
	}

	return bit_char_ptr;
}
