RSAES_PKCS1v1_5Encode(
		      TPM2B       *padded,
		      TPM2B       *message,
		      RAND_STATE  *rand
		      )
{
    UINT32      ps = padded->size - message->size - 3;

    if(message->size > padded->size - 11)
	return TPM_RC_VALUE;

    memcpy(&padded->buffer[padded->size - message->size], message->buffer,
	   message->size);

    padded->buffer[0] = 0;
    padded->buffer[1] = 2;

    DRBG_Generate(rand, &padded->buffer[2], (UINT16)ps);

    padded->buffer[2 + ps] = 0;


    for(ps++; ps > 1; ps--)
	{
	    if(padded->buffer[ps] == 0)
		padded->buffer[ps] = 0x55;


	}
    return TPM_RC_SUCCESS;
}
