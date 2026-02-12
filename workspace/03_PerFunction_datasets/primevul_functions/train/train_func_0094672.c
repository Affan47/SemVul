static int calc_replydigest(RADIUS_PACKET *packet, RADIUS_PACKET *original,
			    const char *secret)
{
	uint8_t		calc_digest[AUTH_VECTOR_LEN];
	MD5_CTX		context;


	if (original == NULL) {
		return 3;
	}


	memcpy(packet->data + 4, original->vector, AUTH_VECTOR_LEN);


	MD5Init(&context);
	MD5Update(&context, packet->data, packet->data_len);
	MD5Update(&context, secret, strlen(secret));
	MD5Final(calc_digest, &context);


	memcpy(packet->data + 4, packet->vector, AUTH_VECTOR_LEN);


	packet->verified =
		memcmp(packet->vector, calc_digest, AUTH_VECTOR_LEN) ? 2 : 0;
	return packet->verified;
}
