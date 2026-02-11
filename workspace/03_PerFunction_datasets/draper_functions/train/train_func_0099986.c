per_insert_octets_except_unused(int no_bytes, unsigned char **input_ptr,
	unsigned char **output_ptr, int *unused, int in_unused) {
    unsigned char *in_ptr = *input_ptr;
    unsigned char *ptr = *output_ptr;
    int val, no_bits;
    int ret = 0;

    if (in_unused == 0) {
	if ((ret = per_insert_octets_unaligned(no_bytes, &in_ptr, &ptr, *unused))
		== ASN1_ERROR
		)
	    return ASN1_ERROR;
    } else {
	if ((ret = per_insert_octets_unaligned(no_bytes - 1, &in_ptr, &ptr, *unused))
		!= ASN1_ERROR) {
	    val = (int) *(++in_ptr);
	    no_bits = 8 - in_unused;


	    if (no_bits < *unused) {
		*ptr = *ptr | (val >> (8 - *unused));
		*unused = *unused - no_bits;
	    } else if (no_bits == *unused) {
		*ptr = *ptr | (val >> (8 - *unused));
		*++ptr = 0x00;
		ret++;
		*unused = 8;
	    } else {
		*ptr = *ptr | (val >> (8 - *unused));
		*++ptr = 0x00;
		ret++;
		*ptr = *ptr | (val << *unused);
		*unused = 8 - (no_bits - *unused);
	    }
	} else
	    return ASN1_ERROR;
    }
    *input_ptr = in_ptr;
    *output_ptr = ptr;
    return ret;
}
