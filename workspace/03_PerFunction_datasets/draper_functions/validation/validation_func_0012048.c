decrypt_and_extract(private_message_t *this, keymat_t *keymat,
						payload_t *previous, encryption_payload_t *encryption)
{
	payload_t *encrypted;
	payload_type_t type;
	chunk_t chunk;
	aead_t *aead;
	size_t bs;
	status_t status = SUCCESS;

	if (!keymat)
	{
		DBG1(DBG_ENC, "found encrypted payload, but no keymat");
		return INVALID_ARG;
	}
	aead = keymat->get_aead(keymat, TRUE);
	if (!aead)
	{
		DBG1(DBG_ENC, "found encrypted payload, but no transform set");
		return INVALID_ARG;
	}
	bs = aead->get_block_size(aead);
	encryption->set_transform(encryption, aead);
	chunk = this->packet->get_data(this->packet);
	if (chunk.len < encryption->get_length(encryption) ||
		chunk.len < bs)
	{
		DBG1(DBG_ENC, "invalid payload length");
		return VERIFY_ERROR;
	}
	if (keymat->get_version(keymat) == IKEV1)
	{

		keymat_v1_t *keymat_v1 = (keymat_v1_t*)keymat;
		chunk_t iv;

		if (keymat_v1->get_iv(keymat_v1, this->message_id, &iv))
		{
			status = encryption->decrypt(encryption, iv);
			if (status == SUCCESS)
			{
				if (!keymat_v1->update_iv(keymat_v1, this->message_id,
						chunk_create(chunk.ptr + chunk.len - bs, bs)))
				{
					status = FAILED;
				}
			}
		}
		else
		{
			status = FAILED;
		}
	}
	else
	{
		chunk.len -= encryption->get_length(encryption);
		status = encryption->decrypt(encryption, chunk);
	}
	if (status != SUCCESS)
	{
		return status;
	}

	while ((encrypted = encryption->remove_payload(encryption)))
	{
		type = encrypted->get_type(encrypted);
		if (previous)
		{
			previous->set_next_type(previous, type);
		}
		else
		{
			this->first_payload = type;
		}
		DBG2(DBG_ENC, "insert decrypted payload of type %N at end of list",
			 payload_type_names, type);
		this->payloads->insert_last(this->payloads, encrypted);
		previous = encrypted;
	}
	return SUCCESS;
}
