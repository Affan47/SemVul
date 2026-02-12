CryptRsaGenerateKey(
		    OBJECT              *rsaKey,

		    RAND_STATE          *rand

		    )
{
    UINT32               i;
    BN_PRIME(bnP);
    BN_PRIME(bnQ);
    BN_RSA(bnD);
    BN_RSA(bnN);
    BN_WORD(bnE);
    UINT32               e;
    int                  keySizeInBits;
    TPMT_PUBLIC         *publicArea = &rsaKey->publicArea;
    TPMT_SENSITIVE      *sensitive = &rsaKey->sensitive;
    TPM_RC               retVal = TPM_RC_NO_RESULT;


    e = publicArea->parameters.rsaDetail.exponent;
    if(e == 0)
	e = RSA_DEFAULT_PUBLIC_EXPONENT;
    if(e < 65537)
	ERROR_RETURN(TPM_RC_RANGE);
    if(e != RSA_DEFAULT_PUBLIC_EXPONENT && !IsPrimeInt(e))
	ERROR_RETURN(TPM_RC_RANGE);
    BnSetWord(bnE, e);


    keySizeInBits = publicArea->parameters.rsaDetail.keyBits;
    if(((keySizeInBits % 1024) != 0)
       || (keySizeInBits > MAX_RSA_KEY_BITS)
       || (keySizeInBits == 0))
	ERROR_RETURN(TPM_RC_VALUE);

    INSTRUMENT_SET(PrimeIndex, PRIME_INDEX(keySizeInBits / 2));
#if SIMULATION && USE_RSA_KEY_CACHE
    if(GET_CACHED_KEY(rsaKey, rand))
	return TPM_RC_SUCCESS;
#endif

    TEST(ALG_NULL_VALUE);
#if USE_OPENSSL_FUNCTIONS_RSA
    if (rand == NULL)
        return OpenSSLCryptRsaGenerateKey(rsaKey, e, keySizeInBits);
#endif

    RsaInitializeExponent(&rsaKey->privateExponent);


    for(i = 1; (retVal != TPM_RC_SUCCESS) && (i != 100); i++)
	{
	    if(_plat__IsCanceled())
		ERROR_RETURN(TPM_RC_CANCELED);
	    BnGeneratePrimeForRSA(bnP, keySizeInBits / 2, e, rand);
	    INSTRUMENT_INC(PrimeCounts[PrimeIndex]);


	    if(BnEqualZero(bnQ))
		{

		    BnCopy(bnQ, bnP);
		    continue;
		}


	    if(BnUnsignedCmp(bnP, bnQ) < 0)
		BnSub(bnD, bnQ, bnP);
	    else
		BnSub(bnD, bnP, bnQ);
	    if(BnMsb(bnD) < 100)
		continue;

	    BnMult(bnN, bnP, bnQ);
	    BnTo2B(bnN, &publicArea->unique.rsa.b,
		   (NUMBYTES)BITS_TO_BYTES(keySizeInBits));

	    BnTo2B(bnP, &sensitive->sensitive.rsa.b,
		   (NUMBYTES)BITS_TO_BYTES(keySizeInBits) / 2);


	    if(((publicArea->unique.rsa.t.buffer[0] & 0x80) == 0)
	       || ((sensitive->sensitive.rsa.t.buffer[0] & 0x80) == 0))
		FAIL(FATAL_ERROR_INTERNAL);

	    if(ComputePrivateExponent(bnP, bnQ, bnE, bnN, &rsaKey->privateExponent)
	       != TRUE)
		{


		    if(BnEqualZero(bnQ))
			BnCopy(bnQ, bnP);
		    continue;
		}
	    retVal = TPM_RC_SUCCESS;

	    if(IS_ATTRIBUTE(publicArea->objectAttributes, TPMA_OBJECT, sign))
		{
		    BN_RSA(temp1);
		    BN_RSA(temp2);
		    BnGenerateRandomInRange(temp1, bnN, rand);

		    BnModExp(temp2, temp1, bnE, bnN);

		    RsaPrivateKeyOp(temp2, bnN, bnP, &rsaKey->privateExponent);


		    if(BnUnsignedCmp(temp2, temp1) != 0)
			{
			    BnSetWord(bnQ, 0);
			    retVal = TPM_RC_NO_RESULT;
			}
		}
	}
 Exit:
    if(retVal == TPM_RC_SUCCESS)
	rsaKey->attributes.privateExp = SET;
    return retVal;
}
