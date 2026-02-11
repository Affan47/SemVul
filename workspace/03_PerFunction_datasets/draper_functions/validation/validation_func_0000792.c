addRootElement(int64_t ce, UErrorCode &errorCode) {
    if(U_FAILURE(errorCode) || ce == 0) { return; }

    ce &= INT64_C(0xffffffffffff3fff);
    U_ASSERT((ce & 0xc0) == 0);


    uint32_t p = (uint32_t)(ce >> 32);
    uint32_t secTer = (uint32_t)ce;
    if(secTer == Collation::COMMON_SEC_AND_TER_CE) {
        if(firstHanPrimary <= p && p <= lastHanPrimary) {
            return;
        }
    } else {

        uint32_t s = secTer >> 16;
        uint32_t t = secTer & Collation::ONLY_TERTIARY_MASK;
        if((s != 0 && s < Collation::COMMON_WEIGHT16) || (t != 0 && t < Collation::COMMON_WEIGHT16)) {
            errorCode = U_ILLEGAL_ARGUMENT_ERROR;
            return;
        }
    }

    if((p & 0xff) != 0) {
        errorCode = U_ILLEGAL_ARGUMENT_ERROR;
        return;
    }
    int32_t i = binarySearch(rootElements, ce);
    if(i < 0) {
        rootElements.insertElementAt(ce, ~i, errorCode);
    }
}
