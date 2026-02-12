CryptRsaSelectScheme(
		     TPMI_DH_OBJECT       rsaHandle,
		     TPMT_RSA_DECRYPT    *scheme
		     )
{
    OBJECT              *rsaObject;
    TPMT_ASYM_SCHEME    *keyScheme;
    TPMT_RSA_DECRYPT    *retVal = NULL;

    rsaObject = HandleToObject(rsaHandle);
    keyScheme = &rsaObject->publicArea.parameters.asymDetail.scheme;


    if(keyScheme->scheme == TPM_ALG_NULL)
	{
	    retVal = scheme;
	}


    else if(scheme->scheme == TPM_ALG_NULL)
	{

	    retVal = (TPMT_RSA_DECRYPT *)keyScheme;
	}


    else if(keyScheme->scheme == scheme->scheme
	    && keyScheme->details.anySig.hashAlg == scheme->details.anySig.hashAlg)
	{
	    retVal = scheme;
	}

    return retVal;
}
