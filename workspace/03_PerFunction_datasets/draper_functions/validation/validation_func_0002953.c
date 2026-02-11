mprGetFirstKey(MprHash *hash)
{
    MprKey      *sp;
    int         i;

    mprAssert(hash);

    for (i = 0; i < hash->size; i++) {
        if ((sp = (MprKey*) hash->buckets[i]) != 0) {
            return sp;
        }
    }
    return 0;
}
