ComputePrivateExponent(
		       bigNum               P,
		       bigNum               Q,
		       bigNum               E,
		       bigNum               N,
		       privateExponent_t   *pExp
		       )
{
    BOOL                pOK;
    BOOL                qOK;
#if CRT_FORMAT_RSA == NO
    BN_RSA(bnPhi);

    RsaInitializeExponent(pExp);

    pOK = BnCopy(bnPhi, N);
    pOK = pOK && BnSub(bnPhi, bnPhi, P);
    pOK = pOK && BnSub(bnPhi, bnPhi, Q);
    pOK = pOK && BnAddWord(bnPhi, bnPhi, 1);

    pOK = pOK && BnModInverse((bigNum)&pExp->D, E, bnPhi);
    qOK = pOK;
#else
    BN_PRIME(temp);
    bigNum              pT;

    NOT_REFERENCED(N);
    RsaInitializeExponent(pExp);
    BnCopy((bigNum)&pExp->Q, Q);

    if(BnUnsignedCmp(P, Q) < 0)
	{
	    pT = P;
	    P = Q;
	    Q = pT;
	}

    pOK = BnSubWord(temp, P, 1);
    pOK = pOK && BnModInverse((bigNum)&pExp->dP, E, temp);

    qOK = BnSubWord(temp, Q, 1);
    qOK = qOK && BnModInverse((bigNum)&pExp->dQ, E, temp);

    if(pOK && qOK)
	pOK = qOK = BnModInverse((bigNum)&pExp->qInv, Q, P);
#endif
    if(!pOK)
	BnSetWord(P, 0);
    if(!qOK)
	BnSetWord(Q, 0);
    return pOK && qOK;
}
