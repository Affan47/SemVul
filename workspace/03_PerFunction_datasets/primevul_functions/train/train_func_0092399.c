static int RsaMGF1(enum wc_HashType hType, byte* seed, word32 seedSz,
                                        byte* out, word32 outSz, void* heap)
{
    byte* tmp;

    byte  tmpA[WC_MAX_DIGEST_SIZE + 4];
    byte   tmpF;
    word32 tmpSz;
    int hLen;
    int ret;
    word32 counter;
    word32 idx;
    hLen    = wc_HashGetDigestSize(hType);
    counter = 0;
    idx     = 0;

    (void)heap;


    if (hLen < 0) {
        return hLen;
    }


    if ((seedSz + 4) > sizeof(tmpA) || (word32)hLen > sizeof(tmpA)) {


        tmpSz = ((seedSz + 4) > (word32)hLen)? seedSz + 4: (word32)hLen;
        tmp = (byte*)XMALLOC(tmpSz, heap, DYNAMIC_TYPE_RSA_BUFFER);
        if (tmp == NULL) {
            return MEMORY_E;
        }
        tmpF = 1;
    }
    else {

        tmpSz = sizeof(tmpA);
        tmp  = tmpA;
        tmpF = 0;
    }

    do {
        int i = 0;
        XMEMCPY(tmp, seed, seedSz);


        tmp[seedSz]     = (byte)((counter >> 24) & 0xFF);
        tmp[seedSz + 1] = (byte)((counter >> 16) & 0xFF);
        tmp[seedSz + 2] = (byte)((counter >>  8) & 0xFF);
        tmp[seedSz + 3] = (byte)((counter)       & 0xFF);


        if ((ret = wc_Hash(hType, tmp, (seedSz + 4), tmp, tmpSz)) != 0) {

            if (tmpF) {
                XFREE(tmp, heap, DYNAMIC_TYPE_RSA_BUFFER);
            }
            return ret;
        }

        for (i = 0; i < hLen && idx < outSz; i++) {
            out[idx++] = tmp[i];
        }
        counter++;
    } while (idx < outSz);


    if (tmpF) {
        XFREE(tmp, heap, DYNAMIC_TYPE_RSA_BUFFER);
    }

    return 0;
}
