SECMOD_UpdateSlotList(SECMODModule *mod)
{
    CK_RV crv;
    CK_ULONG count;
    CK_ULONG i, oldCount;
    PRBool freeRef = PR_FALSE;
    void *mark = NULL;
    CK_ULONG *slotIDs = NULL;
    PK11SlotInfo **newSlots = NULL;
    PK11SlotInfo **oldSlots = NULL;

    if (!moduleLock) {
    	PORT_SetError(SEC_ERROR_NOT_INITIALIZED);
	return SECFailure;
    }


    PZ_Lock(mod->refLock);
    freeRef = PR_TRUE;

    crv = PK11_GETTAB(mod)->C_GetSlotList(PR_FALSE, NULL, &count);
    if (crv != CKR_OK) {
	PORT_SetError(PK11_MapError(crv));
	goto loser;
    }


    if (count == mod->slotCount) {
 	PZ_Unlock(mod->refLock);
	return SECSuccess;
    }
    if (count < (CK_ULONG)mod->slotCount) {

	PORT_SetError( SEC_ERROR_INCOMPATIBLE_PKCS11 );
	goto loser;
    }


    slotIDs = PORT_NewArray(CK_SLOT_ID, count);
    if (slotIDs == NULL) {
	goto loser;
    }

    crv = PK11_GETTAB(mod)->C_GetSlotList(PR_FALSE, slotIDs, &count);
    if (crv != CKR_OK) {
	PORT_SetError(PK11_MapError(crv));
	goto loser;
    }
    freeRef = PR_FALSE;
    PZ_Unlock(mod->refLock);
    mark = PORT_ArenaMark(mod->arena);
    if (mark == NULL) {
	goto loser;
    }
    newSlots = PORT_ArenaZNewArray(mod->arena,PK11SlotInfo *,count);


    for (i=0; i < count; i++) {
	PK11SlotInfo *slot = SECMOD_FindSlotByID(mod,slotIDs[i]);

	if (!slot) {

	    slot = PK11_NewSlotInfo(mod);
	    if (!slot) {
		goto loser;
	    }
	    PK11_InitSlot(mod, slotIDs[i], slot);
	    STAN_InitTokenForSlotInfo(NULL, slot);
	}
	newSlots[i] = slot;
    }
    STAN_ResetTokenInterator(NULL);
    PORT_Free(slotIDs);
    slotIDs = NULL;
    PORT_ArenaUnmark(mod->arena, mark);


    SECMOD_GetWriteLock(moduleLock);
    oldCount =mod->slotCount;
    oldSlots = mod->slots;
    mod->slots = newSlots;


    mod->slotCount = count;
    SECMOD_ReleaseWriteLock(moduleLock);

    for (i=0; i < oldCount; i++) {
	PK11_FreeSlot(oldSlots[i]);
    }
    return SECSuccess;

loser:
    if (freeRef) {
	PZ_Unlock(mod->refLock);
    }
    if (slotIDs) {
	PORT_Free(slotIDs);
    }


    if (newSlots) {
	for (i=0; i < count; i++) {
	    if (newSlots[i] == NULL) {
		break;
	    }
	    PK11_FreeSlot(newSlots[i]);
	}
    }

    if (mark) {
 	PORT_ArenaRelease(mod->arena, mark);
    }
    return SECFailure;
}
