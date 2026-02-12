ObjectTerminateEvent(
		     void
		     )
{
    HASH_OBJECT         *hashObject;
    int                  count;
    BYTE                 buffer[MAX_DIGEST_SIZE];
    hashObject = (HASH_OBJECT *)HandleToObject(g_DRTMHandle);

    if(hashObject->attributes.eventSeq)
	{


	    for(count = 0; CryptHashGetAlgByIndex(count) != TPM_ALG_NULL; count++)
		{
		    CryptHashEnd(&hashObject->state.hashState[count], 0, buffer);
		}

	    FlushObject(g_DRTMHandle);
	}
    g_DRTMHandle = TPM_RH_UNASSIGNED;
}
