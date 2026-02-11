SFTK_SlotReInit(SFTKSlot *slot, char *configdir, char *updatedir,
	char *updateID, sftk_token_parameters *params, int moduleIndex)
{
    PRBool needLogin = !params->noKeyDB;
    CK_RV crv;

    slot->hasTokens = PR_FALSE;
    slot->sessionIDConflict = 0;
    slot->sessionCount = 0;
    slot->rwSessionCount = 0;
    slot->needLogin = PR_FALSE;
    slot->isLoggedIn = PR_FALSE;
    slot->ssoLoggedIn = PR_FALSE;
    slot->DB_loaded = PR_FALSE;
    slot->certDB = NULL;
    slot->keyDB = NULL;
    slot->minimumPinLen = 0;
    slot->readOnly = params->readOnly;
    sftk_setStringName(params->tokdes ? params->tokdes :
	sftk_getDefTokName(slot->slotID), slot->tokDescription,
					sizeof(slot->tokDescription),PR_TRUE);
    sftk_setStringName(params->updtokdes ? params->updtokdes : " ",
				slot->updateTokDescription,
				sizeof(slot->updateTokDescription),PR_TRUE);

    if ((!params->noCertDB) || (!params->noKeyDB)) {
	SFTKDBHandle * certHandle = NULL;
	SFTKDBHandle *keyHandle = NULL;
	crv = sftk_DBInit(params->configdir ? params->configdir : configdir,
		params->certPrefix, params->keyPrefix,
		params->updatedir ? params->updatedir : updatedir,
		params->updCertPrefix, params->updKeyPrefix,
		params->updateID  ? params->updateID : updateID,
		params->readOnly, params->noCertDB, params->noKeyDB,
		params->forceOpen,
		moduleIndex == NSC_FIPS_MODULE,
		&certHandle, &keyHandle);
	if (crv != CKR_OK) {
	    goto loser;
	}

	slot->certDB = certHandle;
	slot->keyDB = keyHandle;
    }
    if (needLogin) {

	slot->needLogin =
		(PRBool)!sftk_hasNullPassword(slot, slot->keyDB);
	if ((params->minPW >= 0) && (params->minPW <= SFTK_MAX_PIN)) {
	    slot->minimumPinLen = params->minPW;
	}
	if ((slot->minimumPinLen == 0) && (params->pwRequired)) {
	    slot->minimumPinLen = 1;
	}
	if ((moduleIndex == NSC_FIPS_MODULE) &&
		(slot->minimumPinLen < FIPS_MIN_PIN)) {
	    slot->minimumPinLen = FIPS_MIN_PIN;
	}
    }

    slot->present = PR_TRUE;
    return CKR_OK;

loser:
    SFTK_ShutdownSlot(slot);
    return crv;
}
