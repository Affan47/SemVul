xmlSecGnuTLSDnAttrsEqual(const xmlSecGnuTLSDnAttr * ll, xmlSecSize llSize,
                         const xmlSecGnuTLSDnAttr * rr, xmlSecSize rrSize)
{
    xmlSecSize llNum = 0;
    xmlSecSize rrNum = 0;
    const xmlSecGnuTLSDnAttr * tmp;
    xmlSecSize ii;

    xmlSecAssert2(ll != NULL, -1);
    xmlSecAssert2(llSize > 0, -1);
    xmlSecAssert2(rr != NULL, -1);
    xmlSecAssert2(rrSize > 0, -1);


    for(ii = 0; ii < llSize; ++ii) {
        if(ll[ii].key != NULL) {
            ++llNum;
        }
    }
    for(ii = 0; ii < rrSize; ++ii) {
        if(rr[ii].key != NULL) {
            ++rrNum;
        }
    }
    if(llNum != rrNum) {
        return(0);
    }


    for(ii = 0; ii < llSize; ++ii) {
        if(ll[ii].key == NULL) {
            continue;
        }

        tmp = xmlSecGnuTLSDnAttrrsFind(rr, rrSize, ll[ii].key);
        if(tmp == NULL) {
            return(0);
        }

        if(!xmlStrEqual(ll[ii].value, tmp->value)) {
            return(0);
        }
    }


    return(1);
}
