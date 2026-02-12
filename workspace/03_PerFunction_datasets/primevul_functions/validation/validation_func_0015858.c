RSAES_Decode(
	     TPM2B       *message,
	     TPM2B       *coded
	     )
{
    BOOL        fail = FALSE;
    UINT16      pSize;
    fail = (coded->size < 11);
    fail = (coded->buffer[0] != 0x00) | fail;
    fail = (coded->buffer[1] != 0x02) | fail;
    for(pSize = 2; pSize < coded->size; pSize++)
	{
	    if(coded->buffer[pSize] == 0)
		break;
	}
    pSize++;


    fail = (pSize >= coded->size) | fail;
    fail = ((pSize - 2) < 8) | fail;
    if((message->size < (UINT16)(coded->size - pSize)) || fail)
	return TPM_RC_VALUE;
    message->size = coded->size - pSize;
    memcpy(message->buffer, &coded->buffer[pSize], coded->size - pSize);
    return TPM_RC_SUCCESS;
}
