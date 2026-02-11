genericHgetallCommand(redisClient *c, int flags) {
    robj *o;
    unsigned long count = 0;
    hashTypeIterator *hi;
    void *replylen = NULL;

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptymultibulk)) == NULL
        || checkType(c,o,REDIS_HASH)) return;

    replylen = addDeferredMultiBulkLength(c);
    hi = hashTypeInitIterator(o);
    while (hashTypeNext(hi) != REDIS_ERR) {
        robj *obj;
        unsigned char *v = NULL;
        unsigned int vlen = 0;
        int encoding;

        if (flags & REDIS_HASH_KEY) {
            encoding = hashTypeCurrent(hi,REDIS_HASH_KEY,&obj,&v,&vlen);
            if (encoding == REDIS_ENCODING_HT)
                addReplyBulk(c,obj);
            else
                addReplyBulkCBuffer(c,v,vlen);
            count++;
        }
        if (flags & REDIS_HASH_VALUE) {
            encoding = hashTypeCurrent(hi,REDIS_HASH_VALUE,&obj,&v,&vlen);
            if (encoding == REDIS_ENCODING_HT)
                addReplyBulk(c,obj);
            else
                addReplyBulkCBuffer(c,v,vlen);
            count++;
        }
    }
    hashTypeReleaseIterator(hi);
    setDeferredMultiBulkLength(c,replylen,count);
}
