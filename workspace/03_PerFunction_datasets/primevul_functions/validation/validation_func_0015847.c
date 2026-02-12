CryptRsaEncrypt(
		TPM2B_PUBLIC_KEY_RSA        *cOut,
		TPM2B                       *dIn,
		OBJECT                      *key,
		TPMT_RSA_DECRYPT            *scheme,

		const TPM2B                 *label,
		RAND_STATE                  *rand

		)
{
    TPM_RC                       retVal = TPM_RC_SUCCESS;
    TPM2B_PUBLIC_KEY_RSA         dataIn;


    if(dIn == &cOut->b)
	{
	    MemoryCopy2B(&dataIn.b, dIn, sizeof(dataIn.t.buffer));
	    dIn = &dataIn.b;
	}

    cOut->t.size = key->publicArea.unique.rsa.t.size;
    TEST(scheme->scheme);
    switch(scheme->scheme)
	{
	  case ALG_NULL_VALUE:
	      {
		  INT32            i;
		  INT32            dSize = dIn->size;


		  for(i = 0; (i < dSize) && (dIn->buffer[i] == 0); i++);
		  dSize -= i;
		  if(dSize > cOut->t.size)
		      ERROR_RETURN(TPM_RC_VALUE);

		  memset(cOut->t.buffer, 0, cOut->t.size - dSize);

		  memcpy(&cOut->t.buffer[cOut->t.size - dSize], &dIn->buffer[i], dSize);


	      }
	      break;
	  case ALG_RSAES_VALUE:
	    retVal = RSAES_PKCS1v1_5Encode(&cOut->b, dIn, rand);
	    break;
	  case ALG_OAEP_VALUE:
	    retVal = OaepEncode(&cOut->b, scheme->details.oaep.hashAlg, label, dIn,
				rand);
	    break;
	  default:
	    ERROR_RETURN(TPM_RC_SCHEME);
	    break;
	}


    if(retVal == TPM_RC_SUCCESS)

	retVal = RSAEP(&cOut->b, key);
 Exit:
    return retVal;
}
