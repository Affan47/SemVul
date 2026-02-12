RsaPrivateKeyOp(
		bigNum               inOut,
		bigNum               N,
		bigNum               P,
		privateExponent_t   *pExp
		)
{
    BOOL                 OK;
#if CRT_FORMAT_RSA == NO
    (P);
    OK = BnModExp(inOut, inOut, (bigNum)&pExp->D, N);
#else
    BN_RSA(M1);
    BN_RSA(M2);
    BN_RSA(M);
    BN_RSA(H);
    bigNum              Q = (bigNum)&pExp->Q;
    NOT_REFERENCED(N);


    if(BnUnsignedCmp(P, Q) < 0)
	{
	    bigNum      T = P;
	    P = Q;
	    Q = T;
	}

    OK = BnModExp(M1, inOut, (bigNum)&pExp->dP, P);

    OK = OK && BnModExp(M2, inOut, (bigNum)&pExp->dQ, Q);


    OK = OK && BnSub(H, P, M2);
    OK = OK && BnAdd(H, H, M1);
    OK = OK && BnModMult(H, H, (bigNum)&pExp->qInv, P);

    OK = OK && BnMult(M, H, Q);
    OK = OK && BnAdd(inOut, M2, M);
#endif
    return OK;
}
