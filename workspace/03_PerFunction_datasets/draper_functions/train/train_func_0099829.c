Jim_GetAssocData(Jim_Interp *interp, const char *key)
{
    Jim_HashEntry *entryPtr = Jim_FindHashEntry(&interp->assocData, key);

    if (entryPtr != NULL) {
        AssocDataValue *assocEntryPtr = (AssocDataValue *) entryPtr->u.val;

        return assocEntryPtr->data;
    }
    return NULL;
}
