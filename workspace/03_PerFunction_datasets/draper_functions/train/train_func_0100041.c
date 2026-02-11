bjoin (const struct bstrList * bl, const_bstring sep) {
bstring b;
int i, c, v;

	if (bl == NULL || bl->qty < 0) return NULL;
	if (sep != NULL && (sep->slen < 0 || sep->data == NULL)) return NULL;

	for (i = 0, c = 1; i < bl->qty; i++) {
		v = bl->entry[i]->slen;
		if (v < 0) return NULL;
		c += v;
		if (c < 0) return NULL;
	}

	if (sep != NULL) c += (bl->qty - 1) * sep->slen;

	b = (bstring) bstr__alloc (sizeof (struct tagbstring));
	if (NULL == b) return NULL;
	b->data = (unsigned char *) bstr__alloc (c);
	if (b->data == NULL) {
		bstr__free (b);
		return NULL;
	}

	b->mlen = c;
	b->slen = c-1;

	for (i = 0, c = 0; i < bl->qty; i++) {
		if (i > 0 && sep != NULL) {
			bstr__memcpy (b->data + c, sep->data, sep->slen);
			c += sep->slen;
		}
		v = bl->entry[i]->slen;
		bstr__memcpy (b->data + c, bl->entry[i]->data, v);
		c += v;
	}
	b->data[c] = (unsigned char) '\0';
	return b;
}
