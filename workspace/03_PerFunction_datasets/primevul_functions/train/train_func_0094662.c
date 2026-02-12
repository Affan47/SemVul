int rad_tunnel_pwdecode(uint8_t *passwd, int *pwlen, const char *secret,
			const char *vector)
{
	uint8_t		buffer[AUTH_VECTOR_LEN + MAX_STRING_LEN + 3];
	uint8_t		digest[AUTH_VECTOR_LEN];
	uint8_t		decrypted[MAX_STRING_LEN + 1];
	int		secretlen;
	unsigned	i, n, len;

	len = *pwlen;


	if (len < 2) {
		librad_log("tunnel password is too short");
		return -1;
	}


	if (len <= 3) {
		passwd[0] = 0;
		*pwlen = 0;
		return 0;
	}

	len -= 2;


	secretlen = strlen(secret);


	memcpy(buffer, secret, secretlen);
	memcpy(buffer + secretlen, vector, AUTH_VECTOR_LEN);
	memcpy(buffer + secretlen + AUTH_VECTOR_LEN, passwd, 2);
	librad_md5_calc(digest, buffer, secretlen + AUTH_VECTOR_LEN + 2);


	n = passwd[2] ^ digest[0];
	if (n >= len) {
		librad_log("tunnel password is too long for the attribute");
		return -1;
	}


	for (n = 0; n < len; n += AUTH_PASS_LEN) {
		for (i = 0; i < AUTH_PASS_LEN; i++) {
			decrypted[n + i] = passwd[n + i + 2] ^ digest[i];


			if ((n + i) == len) break;
		}


		memcpy(buffer + secretlen, passwd + n + 2, AUTH_PASS_LEN);
		librad_md5_calc(digest, buffer, secretlen + AUTH_PASS_LEN);
	}


	memcpy(passwd, decrypted + 1, decrypted[0]);
	passwd[decrypted[0]] = 0;
	*pwlen = decrypted[0];

	return decrypted[0];
}
