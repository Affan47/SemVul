SECKEY_ConvertAndDecodePublicKeyAndChallenge(char *pkacstr, char *challenge,
								void *wincx)
{
    CERTSubjectPublicKeyInfo *spki = NULL;
    CERTPublicKeyAndChallenge pkac;
    SECStatus rv;
    SECItem signedItem;
    PLArenaPool *arena = NULL;
    CERTSignedData sd;
    SECItem sig;
    SECKEYPublicKey *pubKey = NULL;
    unsigned int len;

    signedItem.data = NULL;


    rv = ATOB_ConvertAsciiToItem(&signedItem, pkacstr);
    if (rv != SECSuccess) {
	goto loser;
    }


    arena = PORT_NewArena(DER_DEFAULT_CHUNKSIZE);
    if (arena == NULL) {
	goto loser;
    }


    PORT_Memset(&sd, 0, sizeof(CERTSignedData));
    rv = SEC_QuickDERDecodeItem(arena, &sd, CERT_SignedDataTemplate, &signedItem );
    if ( rv ) {
	goto loser;
    }


    PORT_Memset(&pkac, 0, sizeof(CERTPublicKeyAndChallenge));
    rv = SEC_QuickDERDecodeItem(arena, &pkac, CERT_PublicKeyAndChallengeTemplate,
			    &sd.data);
    if ( rv ) {
	goto loser;
    }


    spki = SECKEY_DecodeDERSubjectPublicKeyInfo(&pkac.spki);
    if ( spki == NULL ) {
	goto loser;
    }


    pubKey = seckey_ExtractPublicKey(spki);
    if ( pubKey == NULL ) {
	goto loser;
    }


    sig = sd.signature;
    DER_ConvertBitString(&sig);
    rv = VFY_VerifyDataWithAlgorithmID(sd.data.data, sd.data.len, pubKey, &sig,
			&(sd.signatureAlgorithm), NULL, wincx);
    if ( rv != SECSuccess ) {
	goto loser;
    }


    if ( challenge ) {
	len = PORT_Strlen(challenge);

	if ( len != pkac.challenge.len ) {
	    goto loser;
	}

	if ( PORT_Memcmp(challenge, pkac.challenge.data, len) != 0 ) {
	    goto loser;
	}
    }
    goto done;

loser:

    if ( spki ) {
	SECKEY_DestroySubjectPublicKeyInfo(spki);
    }
    spki = NULL;

done:
    if ( signedItem.data ) {
	PORT_Free(signedItem.data);
    }
    if ( arena ) {
	PORT_FreeArena(arena, PR_FALSE);
    }
    if ( pubKey ) {
	SECKEY_DestroyPublicKey(pubKey);
    }

    return spki;
}
