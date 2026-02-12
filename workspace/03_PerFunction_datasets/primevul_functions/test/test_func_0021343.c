ObjectCreateEventSequence(
			  TPM2B_AUTH      *auth,
			  TPMI_DH_OBJECT  *newHandle
			  )
{
    HASH_OBJECT         *hashObject = AllocateSequenceSlot(newHandle, auth);
    UINT32               count;
    TPM_ALG_ID           hash;

    if(hashObject == NULL)
	return TPM_RC_OBJECT_MEMORY;

    hashObject->attributes.eventSeq = SET;

    for(count = 0; (hash = CryptHashGetAlgByIndex(count)) != TPM_ALG_NULL; count++)
	CryptHashStart(&hashObject->state.hashState[count], hash);
    return TPM_RC_SUCCESS;
}
