setTypeSize(robj *subject) {
    if (subject->encoding == REDIS_ENCODING_HT) {
        return dictSize((dict*)subject->ptr);
    } else if (subject->encoding == REDIS_ENCODING_INTSET) {
        return intsetLen((intset*)subject->ptr);
    } else {
        redisPanic("Unknown set encoding");
    }
}
