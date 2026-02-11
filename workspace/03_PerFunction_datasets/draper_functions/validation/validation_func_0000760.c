ssl2_get_cipher_by_char(const unsigned char *p)
	{
	SSL_CIPHER c;
	const SSL_CIPHER *cp;
	unsigned long id;

	id=0x02000000L|((unsigned long)p[0]<<16L)|
		((unsigned long)p[1]<<8L)|(unsigned long)p[2];
	c.id=id;
	cp = OBJ_bsearch_ssl_cipher_id(&c, ssl2_ciphers, SSL2_NUM_CIPHERS);
	if ((cp == NULL) || (cp->valid == 0))
		return NULL;
	else
		return cp;
	}
