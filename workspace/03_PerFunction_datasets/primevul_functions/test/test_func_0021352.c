ComputeQualifiedName(
		     TPM_HANDLE       parentHandle,
		     TPM_ALG_ID       nameAlg,
		     TPM2B_NAME      *name,
		     TPM2B_NAME      *qualifiedName
		     )
{
    HASH_STATE      hashState;
    TPM2B_NAME      parentName;
    if(parentHandle == TPM_RH_UNASSIGNED)
	{
	    MemoryCopy2B(&qualifiedName->b, &name->b, sizeof(qualifiedName->t.name));
	    *qualifiedName = *name;
	}
    else
	{
	    GetQualifiedName(parentHandle, &parentName);


	    qualifiedName->t.size = CryptHashStart(&hashState, nameAlg);

	    CryptDigestUpdate2B(&hashState, &parentName.b);

	    CryptDigestUpdate2B(&hashState, &name->b);

	    CryptHashEnd(&hashState, qualifiedName->t.size,
			 &qualifiedName->t.name[2]);
	    UINT16_TO_BYTE_ARRAY(nameAlg, qualifiedName->t.name);
	    qualifiedName->t.size += 2;
	}
    return;
}
