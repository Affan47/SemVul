Jsi_TreeEntry *Jsi_TreeObjSetValue(Jsi_Obj *obj, const char *key, Jsi_Value *val, int isstrkey) {
    Jsi_Tree *treePtr = obj->tree;
    bool isNew;
    Jsi_TreeEntry *hPtr;
    Jsi_Interp *interp = treePtr->opts.interp;
    if (!isstrkey) {
        const char *okey = key;
        Jsi_MapEntry *hePtr = Jsi_MapEntryNew(interp->strKeyTbl, key, &isNew);
        key = (const char*)Jsi_MapKeyGet(hePtr, 0);
        if (!key) {
            Jsi_MapEntry *hePtr = Jsi_MapEntryNew(interp->strKeyTbl, okey, &isNew);
            key = (const char*)Jsi_MapKeyGet(hePtr, 0);
        }
    }

    hPtr = Jsi_TreeEntryNew(treePtr, key, &isNew);
    if (!hPtr)
        return NULL;
    if (val)
        SIGASSERT(val,VALUE);
    if (!isNew)
        Jsi_ValueReplace(interp, (Jsi_Value**)&(hPtr->value), val);
    else {
        hPtr->value = val;
        if (val)
            Jsi_IncrRefCount(interp, val);
    }


    return hPtr;
}
