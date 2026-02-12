ObjectCreateHashSequence(
			 TPMI_ALG_HASH    hashAlg,
			 TPM2B_AUTH      *auth,
			 TPMI_DH_OBJECT  *newHandle
			 )
{
    HASH_OBJECT         *hashObject = AllocateSequenceSlot(newHandle, auth);

    if(hashObject == NULL)
	return TPM_RC_OBJECT_MEMORY;

    hashObject->attributes.hashSeq = SET;

    CryptHashStart(&hashObject->state.hashState[0], hashAlg);
    return TPM_RC_SUCCESS;
}
