pkcs5_pbkdf2(const char *hash,
			const char *P, size_t Plen,
			const char *S, size_t Slen,
			unsigned int c, unsigned int dkLen,
			char *DK, int perfcheck)
{
	struct crypt_hmac *hmac;
	char U[MAX_PRF_BLOCK_LEN];
	char T[MAX_PRF_BLOCK_LEN];
	int i, k, rc = -EINVAL;
	unsigned int u, hLen, l, r;
	size_t tmplen = Slen + 4;
	char *tmp;

	tmp = alloca(tmplen);
	if (tmp == NULL)
		return -ENOMEM;

	hLen = crypt_hmac_size(hash);
	if (hLen == 0 || hLen > MAX_PRF_BLOCK_LEN)
		return -EINVAL;

	if (c == 0)
		return -EINVAL;

	if (dkLen == 0)
		return -EINVAL;


	if (dkLen > 4294967295U)
		return -EINVAL;


	l = dkLen / hLen;
	if (dkLen % hLen)
		l++;
	r = dkLen - (l - 1) * hLen;


	if (crypt_hmac_init(&hmac, hash, P, Plen))
		return -EINVAL;

	for (i = 1; (uint) i <= l; i++) {
		memset(T, 0, hLen);

		for (u = 1; u <= c ; u++) {
			if (u == 1) {
				memcpy(tmp, S, Slen);
				tmp[Slen + 0] = (i & 0xff000000) >> 24;
				tmp[Slen + 1] = (i & 0x00ff0000) >> 16;
				tmp[Slen + 2] = (i & 0x0000ff00) >> 8;
				tmp[Slen + 3] = (i & 0x000000ff) >> 0;

				if (crypt_hmac_write(hmac, tmp, tmplen))
					goto out;
			} else {
				if (crypt_hmac_write(hmac, U, hLen))
					goto out;
			}

			if (crypt_hmac_final(hmac, U, hLen))
				goto out;

			for (k = 0; (uint) k < hLen; k++)
				T[k] ^= U[k];

			if (perfcheck && __PBKDF2_performance) {
				rc = 0;
				goto out;
			}

			if (perfcheck)
				__PBKDF2_global_j++;
		}

		memcpy(DK + (i - 1) * hLen, T, (uint) i == l ? r : hLen);
	}
	rc = 0;
out:
	crypt_hmac_destroy(hmac);
	return rc;
}
