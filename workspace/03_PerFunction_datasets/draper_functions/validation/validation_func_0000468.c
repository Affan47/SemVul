ssl3_CacheWrappedMasterSecret(sslSocket *ss, sslSessionID *sid,
    ssl3CipherSpec *spec, SSL3KEAType effectiveExchKeyType)
{
    PK11SymKey *      wrappingKey  = NULL;
    PK11SlotInfo *    symKeySlot;
    void *            pwArg        = ss->pkcs11PinArg;
    SECStatus         rv           = SECFailure;
    PRBool            isServer     = ss->sec.isServer;
    CK_MECHANISM_TYPE mechanism    = CKM_INVALID_MECHANISM;
    symKeySlot = PK11_GetSlotFromKey(spec->master_secret);
    if (!isServer) {
	int  wrapKeyIndex;
	int  incarnation;


	sid->u.ssl3.masterWrapIndex  = wrapKeyIndex =
				       PK11_GetCurrentWrapIndex(symKeySlot);
	PORT_Assert(wrapKeyIndex == 0);

	sid->u.ssl3.masterWrapSeries = incarnation =
				       PK11_GetSlotSeries(symKeySlot);
	sid->u.ssl3.masterSlotID   = PK11_GetSlotID(symKeySlot);
	sid->u.ssl3.masterModuleID = PK11_GetModuleID(symKeySlot);
	sid->u.ssl3.masterValid    = PR_TRUE;


	wrappingKey = PK11_GetWrapKey(symKeySlot, wrapKeyIndex,
				      CKM_INVALID_MECHANISM, incarnation,
				      pwArg);
	if (wrappingKey) {
	    mechanism = PK11_GetMechanism(wrappingKey);
	} else {
	    int keyLength;


	    mechanism = PK11_GetBestWrapMechanism(symKeySlot);
	    keyLength = PK11_GetBestKeyLength(symKeySlot, mechanism);


	    wrappingKey = PK11_KeyGen(symKeySlot, mechanism, NULL,
				      keyLength, pwArg);
	    if (wrappingKey) {
		PK11_SetWrapKey(symKeySlot, wrapKeyIndex, wrappingKey);
	    }
	}
    } else {

	mechanism = PK11_GetBestWrapMechanism(symKeySlot);
	if (mechanism != CKM_INVALID_MECHANISM) {
	    wrappingKey =
		getWrappingKey(ss, symKeySlot, effectiveExchKeyType,
			       mechanism, pwArg);
	    if (wrappingKey) {
		mechanism = PK11_GetMechanism(wrappingKey);
	    }
	}
    }

    sid->u.ssl3.masterWrapMech = mechanism;
    PK11_FreeSlot(symKeySlot);

    if (wrappingKey) {
	SECItem wmsItem;

	wmsItem.data = sid->u.ssl3.keys.wrapped_master_secret;
	wmsItem.len  = sizeof sid->u.ssl3.keys.wrapped_master_secret;
	rv = PK11_WrapSymKey(mechanism, NULL, wrappingKey,
			     spec->master_secret, &wmsItem);

	sid->u.ssl3.keys.wrapped_master_secret_len = wmsItem.len;
	PK11_FreeSymKey(wrappingKey);
    }
    return rv;
}
