RSADP(
      TPM2B           *inOut,
      OBJECT          *key
      )
{
    BN_RSA_INITIALIZED(bnM, inOut);
    BN_RSA_INITIALIZED(bnN, &key->publicArea.unique.rsa);
    BN_RSA_INITIALIZED(bnP, &key->sensitive.sensitive.rsa);
    if(BnUnsignedCmp(bnM, bnN) >= 0)
	return TPM_RC_SIZE;


    if(!key->attributes.privateExp)
	CryptRsaLoadPrivateExponent(key);
    if(!RsaPrivateKeyOp(bnM, bnN, bnP, &key->privateExponent))
	FAIL(FATAL_ERROR_INTERNAL);
    BnTo2B(bnM, inOut, inOut->size);
    return TPM_RC_SUCCESS;
}
