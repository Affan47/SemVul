ssl3_CreateRSAStepDownKeys(sslSocket *ss)
{
    SECStatus             rv  	 = SECSuccess;
    SECKEYPrivateKey *    privKey;
    SECKEYPublicKey *     pubKey;

    if (ss->stepDownKeyPair)
	ssl3_FreeKeyPair(ss->stepDownKeyPair);
    ss->stepDownKeyPair = NULL;
#ifndef HACKED_EXPORT_SERVER

    if (PK11_GetPrivateModulusLen(ss->serverCerts[kt_rsa].SERVERKEY) >
                                                     EXPORT_RSA_KEY_LENGTH) {

	privKey = SECKEY_CreateRSAPrivateKey(EXPORT_RSA_KEY_LENGTH * BPB,
					     &pubKey, NULL);
    	if (!privKey || !pubKey ||
	    !(ss->stepDownKeyPair = ssl3_NewKeyPair(privKey, pubKey))) {
	    ssl_MapLowLevelError(SEC_ERROR_KEYGEN_FAIL);
	    rv = SECFailure;
	}
    }
#endif
    return rv;
}
