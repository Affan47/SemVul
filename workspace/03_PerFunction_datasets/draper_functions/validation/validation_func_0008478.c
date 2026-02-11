get_nonce(message_t *message, chunk_t *n)
{
	nonce_payload_t *nonce;
	nonce = (nonce_payload_t*)message->get_payload(message, NONCE_V1);
	if (nonce)
	{
		*n = nonce->get_nonce(nonce);
		return TRUE;
	}
	return FALSE;
}
