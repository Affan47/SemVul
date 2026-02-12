static int verify_packet(char *secret, AUTH_HDR *response, AUTH_HDR *request)
{
	MD5_CTX my_md5;
	unsigned char	calculated[AUTH_VECTOR_LEN];
	unsigned char	reply[AUTH_VECTOR_LEN];


	memcpy(reply, response->vector, AUTH_VECTOR_LEN);
	memcpy(response->vector, request->vector, AUTH_VECTOR_LEN);


	MD5Init(&my_md5);
	MD5Update(&my_md5, (unsigned char *) response, ntohs(response->length));


	if (*secret) {
		MD5Update(&my_md5, (unsigned char *) secret, strlen(secret));
	}

	MD5Final(calculated, &my_md5);


	if (memcmp(calculated, reply, AUTH_VECTOR_LEN) != 0) {
		return FALSE;
	}
	return TRUE;
}
