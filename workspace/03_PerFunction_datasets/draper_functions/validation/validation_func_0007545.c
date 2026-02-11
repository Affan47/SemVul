brtrimws (bstring b) {
int i;

	if (b == NULL || b->data == NULL || b->mlen < b->slen ||
	    b->slen < 0 || b->mlen <= 0) return BSTR_ERR;

	for (i = b->slen - 1; i >= 0; i--) {
		if (!wspace (b->data[i])) {
			if (b->mlen > i) b->data[i+1] = (unsigned char) '\0';
			b->slen = i + 1;
			return BSTR_OK;
		}
	}

	b->data[0] = (unsigned char) '\0';
	b->slen = 0;
	return BSTR_OK;
}
