static inline int64_t lpGetIntegerIfValid(unsigned char *ele, int *valid) {
    int64_t v;
    unsigned char *e = lpGet(ele,&v,NULL);
    if (e == NULL) {
        if (valid)
            *valid = 1;
        return v;
    }


    long long ll;
    int ret = string2ll((char*)e,v,&ll);
    if (valid)
        *valid = ret;
    else
        serverAssert(ret != 0);
    v = ll;
    return v;
}
