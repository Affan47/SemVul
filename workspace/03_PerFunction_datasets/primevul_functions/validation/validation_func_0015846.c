CryptRsaValidateSignature(
			  TPMT_SIGNATURE  *sig,
			  OBJECT          *key,
			  TPM2B_DIGEST    *digest
			  )
{
    TPM_RC          retVal;


    pAssert(key != NULL && sig != NULL && digest != NULL);
    switch(sig->sigAlg)
	{
	  case ALG_RSAPSS_VALUE:
	  case ALG_RSASSA_VALUE:
	    break;
	  default:
	    return TPM_RC_SCHEME;
	}

    if(sig->signature.rsassa.sig.t.size != key->publicArea.unique.rsa.t.size)
	ERROR_RETURN(TPM_RC_SIGNATURE);
    TEST(sig->sigAlg);

    retVal = RSAEP(&sig->signature.rsassa.sig.b, key);
    if(retVal == TPM_RC_SUCCESS)
	{
	    switch(sig->sigAlg)
		{
		  case ALG_RSAPSS_VALUE:
		    retVal = PssDecode(sig->signature.any.hashAlg, &digest->b,
				       &sig->signature.rsassa.sig.b);
		    break;
		  case ALG_RSASSA_VALUE:
		    retVal = RSASSA_Decode(sig->signature.any.hashAlg, &digest->b,
					   &sig->signature.rsassa.sig.b);
		    break;
		  default:
		    return TPM_RC_SCHEME;
		}
	}
 Exit:
    return (retVal != TPM_RC_SUCCESS) ? TPM_RC_SIGNATURE : TPM_RC_SUCCESS;
}
