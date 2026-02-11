decrypt_fragment(private_message_t *this, keymat_t *keymat,
								 encrypted_fragment_payload_t *fragment)
{
	encrypted_payload_t *encrypted = (encrypted_payload_t*)fragment;
	chunk_t chunk;
	aead_t *aead;
	size_t bs;

	if (!keymat)
	{
		DBG1(DBG_ENC, "found encrypted fragment payload, but no keymat");
		return INVALID_ARG;
	}
	aead = keymat->get_aead(keymat, TRUE);
	if (!aead)
	{
		DBG1(DBG_ENC, "found encrypted fragment payload, but no transform set");
		return INVALID_ARG;
	}
	bs = aead->get_block_size(aead);
	encrypted->set_transform(encrypted, aead);
	chunk = this->packet->get_data(this->packet);
	if (chunk.len < encrypted->get_length(encrypted) ||
		chunk.len < bs)
	{
		DBG1(DBG_ENC, "invalid payload length");
		return VERIFY_ERROR;
	}
	chunk.len -= encrypted->get_length(encrypted);
	return encrypted->decrypt(encrypted, chunk);
}
