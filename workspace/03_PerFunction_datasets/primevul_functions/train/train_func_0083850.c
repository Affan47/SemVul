int tls1_cbc_remove_padding(const SSL* s,
			    SSL3_RECORD *rec,
			    unsigned block_size,
			    unsigned mac_size)
	{
	unsigned padding_length, good, to_check, i;
	const char has_explicit_iv =
		s->version >= TLS1_1_VERSION || s->version == DTLS1_VERSION;
	const unsigned overhead = 1  +
				  mac_size +
				  (has_explicit_iv ? block_size : 0);


	if (overhead > rec->length)
		return 0;


	if (has_explicit_iv)
		{
		rec->data += block_size;
		rec->input += block_size;
		rec->length -= block_size;
		}

	padding_length = rec->data[rec->length-1];


	if ( (s->options&SSL_OP_TLS_BLOCK_PADDING_BUG) && !s->expand)
		{

		if ((memcmp(s->s3->read_sequence, "\0\0\0\0\0\0\0\0",8) == 0) &&
		    !(padding_length & 1))
			{
			s->s3->flags|=TLS1_FLAGS_TLS_PADDING_BUG;
			}
		if ((s->s3->flags & TLS1_FLAGS_TLS_PADDING_BUG) &&
		    padding_length > 0)
			{
			padding_length--;
			}
		}

	if (EVP_CIPHER_flags(s->enc_read_ctx->cipher)&EVP_CIPH_FLAG_AEAD_CIPHER)
		{

		rec->length -= padding_length;
		return 1;
		}

	good = constant_time_ge(rec->length, overhead+padding_length);


	to_check = 255;
	if (to_check > rec->length-1)
		to_check = rec->length-1;

	for (i = 0; i < to_check; i++)
		{
		unsigned char mask = constant_time_ge(padding_length, i);
		unsigned char b = rec->data[rec->length-1-i];


		good &= ~(mask&(padding_length ^ b));
		}


	good &= good >> 4;
	good &= good >> 2;
	good &= good >> 1;
	good <<= sizeof(good)*8-1;
	good = DUPLICATE_MSB_TO_ALL(good);

	padding_length = good & (padding_length+1);
	rec->length -= padding_length;
	rec->type |= padding_length<<8;

	return (int)((good & 1) | (~good & -1));
	}
