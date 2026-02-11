getFallbackData(const UResourceBundle* resBundle, const char* * resTag, UResourceDataEntry* *realData, Resource *res, UErrorCode *status) {
    UResourceDataEntry *resB = resBundle->fData;
    int32_t indexR = -1;
    int32_t i = 0;
    *res = RES_BOGUS;
    if(resB != NULL) {
        if(resB->fBogus == U_ZERO_ERROR) {
            *res = res_getTableItemByKey(&(resB->fData), resB->fData.rootRes, &indexR, resTag);
            i++;
        }
        if(resBundle->fHasFallback == TRUE) {
            while(*res == RES_BOGUS && resB->fParent != NULL) {
                resB = resB->fParent;
                if(resB->fBogus == U_ZERO_ERROR) {
                    i++;
                    *res = res_getTableItemByKey(&(resB->fData), resB->fData.rootRes, &indexR, resTag);
                }
            }
        }

        if(*res != RES_BOGUS) {
            if(i>1) {
                if(uprv_strcmp(resB->fName, uloc_getDefault())==0 || uprv_strcmp(resB->fName, kRootLocaleName)==0) {
                    *status = U_USING_DEFAULT_WARNING;
                } else {
                    *status = U_USING_FALLBACK_WARNING;
                }
            }
            *realData = resB;
            return (&(resB->fData));
        } else {
            *status = U_MISSING_RESOURCE_ERROR;
            return NULL;
        }
    } else {
            *status = U_MISSING_RESOURCE_ERROR;
            return NULL;
    }
}
