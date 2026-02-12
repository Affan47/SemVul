ObjectCreateHMACSequence(
			 TPMI_ALG_HASH    hashAlg,
			 OBJECT          *keyObject,
			 TPM2B_AUTH      *auth,
			 TPMI_DH_OBJECT  *newHandle
			 )
{
    HASH_OBJECT         *hmacObject;


    hmacObject = AllocateSequenceSlot(newHandle, auth);
    if(hmacObject == NULL)
	return TPM_RC_OBJECT_MEMORY;

    hmacObject->attributes.hmacSeq = SET;
#if !SMAC_IMPLEMENTED
    if(CryptHmacStart(&hmacObject->state.hmacState, hashAlg,
		      keyObject->sensitive.sensitive.bits.b.size,
		      keyObject->sensitive.sensitive.bits.b.buffer) == 0)
#else
	if(CryptMacStart(&hmacObject->state.hmacState,
			 &keyObject->publicArea.parameters,
			 hashAlg, &keyObject->sensitive.sensitive.any.b) == 0)
#endif
	    return TPM_RC_FAILURE;
    return TPM_RC_SUCCESS;
}
