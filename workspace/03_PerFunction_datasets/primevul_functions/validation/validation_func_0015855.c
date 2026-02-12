CryptRsaSign(
	     TPMT_SIGNATURE      *sigOut,
	     OBJECT              *key,
	     TPM2B_DIGEST        *hIn,
	     RAND_STATE          *rand

	     )
{
    TPM_RC                retVal = TPM_RC_SUCCESS;
    UINT16                modSize;

    pAssert(sigOut != NULL && key != NULL && hIn != NULL);
    modSize = key->publicArea.unique.rsa.t.size;

    sigOut->signature.rsapss.sig.t.size = modSize;
    TEST(sigOut->sigAlg);
    switch(sigOut->sigAlg)
	{
	  case ALG_NULL_VALUE:
	    sigOut->signature.rsapss.sig.t.size = 0;
	    return TPM_RC_SUCCESS;
	  case ALG_RSAPSS_VALUE:
	    retVal = PssEncode(&sigOut->signature.rsapss.sig.b,
			       sigOut->signature.rsapss.hash, &hIn->b, rand);
	    break;
	  case ALG_RSASSA_VALUE:
	    retVal = RSASSA_Encode(&sigOut->signature.rsassa.sig.b,
				   sigOut->signature.rsassa.hash, &hIn->b);
	    break;
	  default:
	    retVal = TPM_RC_SCHEME;
	}
    if(retVal == TPM_RC_SUCCESS)
	{

	    retVal = RSADP(&sigOut->signature.rsapss.sig.b, key);
	}
    return retVal;
}
