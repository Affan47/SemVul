static Jsi_RC freeValueTbl(Jsi_Interp *interp, Jsi_HashEntry *hPtr, void *ptr) {
    Jsi_Value *val = (Jsi_Value *)ptr;
    if (!val) return JSI_OK;
    SIGASSERT(val,VALUE);


    Jsi_DecrRefCount(interp, val);
    return JSI_OK;
}
