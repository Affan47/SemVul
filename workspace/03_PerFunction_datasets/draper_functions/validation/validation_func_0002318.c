cmmf_create_first_challenge(CMMFPOPODecKeyChallContent *challContent,
			    long                        inRandom,
			    SECItem                    *senderDER,
			    SECKEYPublicKey            *inPubKey,
			    void                       *passwdArg)
{
    SECOidData     *oidData;
    CMMFChallenge  *challenge;
    SECAlgorithmID *algId;
    PLArenaPool    *poolp;
    SECStatus       rv;

    oidData = SECOID_FindOIDByTag(SEC_OID_SHA1);
    if (oidData == NULL) {
        return SECFailure;
    }
    poolp = challContent->poolp;
    challenge = PORT_ArenaZNew(poolp, CMMFChallenge);
    if (challenge == NULL) {
        return SECFailure;
    }
    algId = challenge->owf = PORT_ArenaZNew(poolp, SECAlgorithmID);
    if (algId == NULL) {
        return SECFailure;
    }
    rv = SECITEM_CopyItem(poolp, &algId->algorithm, &oidData->oid);
    if (rv != SECSuccess) {
        return SECFailure;
    }
    rv = cmmf_create_witness_and_challenge(poolp, challenge, inRandom,
					   senderDER, inPubKey, passwdArg);
    challContent->challenges[0] = (rv == SECSuccess) ? challenge : NULL;
    challContent->numChallenges++;
    return rv ;
}
