ucnv_extMatchToU(const int32_t *cx, int8_t sisoState,
                 const char *pre, int32_t preLength,
                 const char *src, int32_t srcLength,
                 uint32_t *pMatchValue,
                 UBool , UBool flush) {
    const uint32_t *toUTable, *toUSection;

    uint32_t value, matchValue;
    int32_t i, j, idx, length, matchLength;
    uint8_t b;

    if(cx==NULL || cx[UCNV_EXT_TO_U_LENGTH]<=0) {
        return 0;
    }


    toUTable=UCNV_EXT_ARRAY(cx, UCNV_EXT_TO_U_INDEX, uint32_t);
    idx=0;

    matchValue=0;
    i=j=matchLength=0;

    if(sisoState==0) {

        if(preLength>1) {
            return 0;
        } else if(preLength==1) {
            srcLength=0;
        } else  {
            if(srcLength>1) {
                srcLength=1;
            }
        }
        flush=TRUE;
    }


    for(;;) {

        toUSection=toUTable+idx;


        value=*toUSection++;
        length=UCNV_EXT_TO_U_GET_BYTE(value);
        value=UCNV_EXT_TO_U_GET_VALUE(value);
        if( value!=0 &&
            (UCNV_EXT_TO_U_IS_ROUNDTRIP(value) ||
             TO_U_USE_FALLBACK(useFallback)) &&
            UCNV_EXT_TO_U_VERIFY_SISO_MATCH(sisoState, i+j)
        ) {

            matchValue=value;
            matchLength=i+j;
        }


        if(i<preLength) {
            b=(uint8_t)pre[i++];
        } else if(j<srcLength) {
            b=(uint8_t)src[j++];
        } else {

            if(flush || (length=(i+j))>UCNV_EXT_MAX_BYTES) {


                break;
            } else {

                return -length;
            }
        }


        value=ucnv_extFindToU(toUSection, length, b);
        if(value==0) {

            break;
        } else {
            if(UCNV_EXT_TO_U_IS_PARTIAL(value)) {

                idx=(int32_t)UCNV_EXT_TO_U_GET_PARTIAL_INDEX(value);
            } else {
                if( (UCNV_EXT_TO_U_IS_ROUNDTRIP(value) ||
                     TO_U_USE_FALLBACK(useFallback)) &&
                    UCNV_EXT_TO_U_VERIFY_SISO_MATCH(sisoState, i+j)
                ) {

                    matchValue=value;
                    matchLength=i+j;
                } else {

                }
                break;
            }
        }
    }

    if(matchLength==0) {

        return 0;
    }


    *pMatchValue=UCNV_EXT_TO_U_MASK_ROUNDTRIP(matchValue);
    return matchLength;
}
