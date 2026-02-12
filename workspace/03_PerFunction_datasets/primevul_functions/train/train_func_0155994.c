MillerRabin(
	    bigNum           bnW,
	    RAND_STATE      *rand
	    )
{
    BN_MAX(bnWm1);
    BN_PRIME(bnM);
    BN_PRIME(bnB);
    BN_PRIME(bnZ);
    BOOL             ret = FALSE;
    unsigned int     a;
    unsigned int     j;
    int              wLen;
    int              i;
    int              iterations = MillerRabinRounds(BnSizeInBits(bnW));

    INSTRUMENT_INC(MillerRabinTrials[PrimeIndex]);
    pAssert(bnW->size > 1);

    BnSubWord(bnWm1, bnW, 1);
    pAssert(bnWm1->size != 0);


    i = bnWm1->size * RADIX_BITS;

    for(a = 1;
	(a < (bnWm1->size * RADIX_BITS)) &&
	    (BnTestBit(bnWm1, a) == 0);
	a++);

    BnShiftRight(bnM, bnWm1, a);

    wLen = BnSizeInBits(bnW);

    for(i = 0; i < iterations; i++)
	{


	    do
		{
		    BnGetRandomBits(bnB, wLen, rand);

		} while((BnUnsignedCmpWord(bnB, 1) <= 0)
			|| (BnUnsignedCmp(bnB, bnWm1) >= 0));


	    BnModExp(bnZ, bnB, bnM, bnW);

	    if((BnUnsignedCmpWord(bnZ, 1) == 0)
	       || (BnUnsignedCmp(bnZ, bnWm1) == 0))
		goto step4point7;

	    for(j = 1; j < a; j++)
		{

		    BnModMult(bnZ, bnZ, bnZ, bnW);

		    if(BnUnsignedCmp(bnZ, bnWm1) == 0)
			goto step4point7;

		    if(BnEqualWord(bnZ, 1))
			goto step4point6;
		}

	step4point6:
	    INSTRUMENT_INC(failedAtIteration[i]);
	    goto end;

	step4point7:
	    continue;
	}

    ret = TRUE;
 end:
    return ret;
}
