snmp_clone_mem(void **dstPtr, const void *srcPtr, unsigned len)
{
    *dstPtr = NULL;
    if (srcPtr) {
        *dstPtr = malloc(len + 1);
        if (!*dstPtr) {
            return 1;
        }
        memmove(*dstPtr, srcPtr, len);


        ((char *) *dstPtr)[len] = 0;
    }
    return 0;
}
