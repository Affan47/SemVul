void Jsi_IterObjFree(Jsi_IterObj *iobj)
{
    if (!iobj->isArrayList) {
        uint i;
        for (i = 0; i < iobj->count; i++) {
            if (iobj->keys[i]) {

            }
        }
        Jsi_Free(iobj->keys);
    }
    Jsi_Free(iobj);
}
