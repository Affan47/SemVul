openssldh_tofile(const dst_key_t *key, const char *directory) {
	int i;
	DH *dh;
	dst_private_t priv;
	unsigned char *bufs[4];
	isc_result_t result;

	if (key->keydata.dh == NULL)
		return (DST_R_NULLKEY);

	if (key->external)
		return (DST_R_EXTERNALKEY);

	dh = key->keydata.dh;

	memset(bufs, 0, sizeof(bufs));
	for (i = 0; i < 4; i++) {
		bufs[i] = isc_mem_get(key->mctx, BN_num_bytes(dh->p));
		if (bufs[i] == NULL) {
			result = ISC_R_NOMEMORY;
			goto fail;
		}
	}

	i = 0;

	priv.elements[i].tag = TAG_DH_PRIME;
	priv.elements[i].length = BN_num_bytes(dh->p);
	BN_bn2bin(dh->p, bufs[i]);
	priv.elements[i].data = bufs[i];
	i++;

	priv.elements[i].tag = TAG_DH_GENERATOR;
	priv.elements[i].length = BN_num_bytes(dh->g);
	BN_bn2bin(dh->g, bufs[i]);
	priv.elements[i].data = bufs[i];
	i++;

	priv.elements[i].tag = TAG_DH_PRIVATE;
	priv.elements[i].length = BN_num_bytes(dh->priv_key);
	BN_bn2bin(dh->priv_key, bufs[i]);
	priv.elements[i].data = bufs[i];
	i++;

	priv.elements[i].tag = TAG_DH_PUBLIC;
	priv.elements[i].length = BN_num_bytes(dh->pub_key);
	BN_bn2bin(dh->pub_key, bufs[i]);
	priv.elements[i].data = bufs[i];
	i++;

	priv.nelements = i;
	result = dst__privstruct_writefile(key, &priv, directory);
 fail:
	for (i = 0; i < 4; i++) {
		if (bufs[i] == NULL)
			break;
		isc_mem_put(key->mctx, bufs[i], BN_num_bytes(dh->p));
	}
	return (result);
}
