cram_huffman_decode_int(cram_slice *slice, cram_codec *c,
			    cram_block *in, char *out, int *out_size) {
    int32_t *out_i = (int32_t *)out;
    int i, n, ncodes = c->huffman.ncodes;
    const cram_huffman_code * const codes = c->huffman.codes;

    for (i = 0, n = *out_size; i < n; i++) {
	int idx = 0;
	int val = 0, len = 0, last_len = 0;


	for (;;) {
	    int dlen = codes[idx].len - last_len;
	    if (dlen <= 0 || (in->alloc - in->byte)*8 + in->bit + 7 < dlen)
		return -1;


	    last_len = (len  += dlen);
	    for (; dlen; dlen--) GET_BIT_MSB(in, val);

	    idx = val - codes[idx].p;
	    if (idx >= ncodes || idx < 0)
		return -1;

	    if (codes[idx].code == val && codes[idx].len == len) {
		out_i[i] = codes[idx].symbol;
		break;
	    }
	}
    }

    return 0;
}
