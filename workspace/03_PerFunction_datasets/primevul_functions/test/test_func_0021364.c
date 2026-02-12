ObjectLoad(
	   OBJECT          *object,

	   OBJECT          *parent,
	   TPMT_PUBLIC     *publicArea,
	   TPMT_SENSITIVE  *sensitive,

	   TPM_RC           blamePublic,

	   TPM_RC           blameSensitive,

	   TPM2B_NAME      *name
	   )
{
    TPM_RC           result = TPM_RC_SUCCESS;
    BOOL             doCheck;


    if(sensitive == NULL || publicArea->nameAlg == TPM_ALG_NULL)
	{


	    result = SchemeChecks(NULL, publicArea);
	}
    else
	{


	    if(sensitive->seedValue.t.size
	       > CryptHashGetDigestSize(publicArea->nameAlg))
		return TPM_RCS_KEY_SIZE + blameSensitive;

	    result = PublicAttributesValidation(parent, publicArea);
	}
    if(result != TPM_RC_SUCCESS)
	return RcSafeAddToResult(result, blamePublic);


    if(object == NULL)
	doCheck = TRUE;


    else if(parent != NULL)
	doCheck = !IS_ATTRIBUTE(parent->publicArea.objectAttributes,
				TPMA_OBJECT, fixedTPM);
    else


	doCheck = TRUE;


    if(doCheck)
	{

	    result = CryptValidateKeys(publicArea, sensitive, blamePublic,
				       blameSensitive);
	}

    if(object == NULL || result != TPM_RC_SUCCESS)
	return result;

    if(name != NULL)
	object->name = *name;
    else
	object->name.t.size = 0;

    object->publicArea = *publicArea;

    if(sensitive == NULL)
	object->attributes.publicOnly = SET;
    else
	{
	    object->sensitive = *sensitive;
#if ALG_RSA


	    if(publicArea->type == ALG_RSA_VALUE)
		result = CryptRsaLoadPrivateExponent(object);
#endif
	}
    return result;
}
