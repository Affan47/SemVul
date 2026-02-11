boxaDestroy(BOXA  **pboxa)
{
l_int32  i;
BOXA    *boxa;

    PROCNAME("boxaDestroy");

    if (pboxa == NULL) {
        L_WARNING("ptr address is null!", procName);
        return;
    }

    if ((boxa = *pboxa) == NULL)
        return;


    boxa->refcount--;
    if (boxa->refcount <= 0) {
        for (i = 0; i < boxa->n; i++)
            boxDestroy(&boxa->box[i]);
        FREE(boxa->box);
        FREE(boxa);
    }

    *pboxa = NULL;
    return;
}
