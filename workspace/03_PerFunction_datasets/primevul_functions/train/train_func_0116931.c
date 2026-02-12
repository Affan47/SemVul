cdk_pk_fingerprint_get_keyid(const byte * fpr, size_t fprlen, u32 * keyid)
{
	u32 lowbits = 0;


	if (fpr && fprlen == 16) {
		keyid[0] = 0;
		keyid[1] = 0;
		return 0;
	} else if (keyid && fpr) {
		keyid[0] = _cdk_buftou32(fpr + 12);
		keyid[1] = _cdk_buftou32(fpr + 16);
		lowbits = keyid[1];
	} else if (fpr)
		lowbits = _cdk_buftou32(fpr + 16);
	return lowbits;
}
