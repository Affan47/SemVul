appendTail(URegularExpression    *regexp,
                  UChar                **destBuf,
                  int32_t               *destCapacity,
                  UErrorCode            *status)
{


    UBool pendingBufferOverflow = FALSE;
    if (*status == U_BUFFER_OVERFLOW_ERROR && destCapacity != NULL && *destCapacity == 0) {
        pendingBufferOverflow = TRUE;
        *status = U_ZERO_ERROR;
    }

    if (validateRE(regexp, status) == FALSE) {
        return 0;
    }

    if (destCapacity == NULL || destBuf == NULL ||
        *destBuf == NULL && *destCapacity > 0 ||
        *destCapacity < 0)
    {
        *status = U_ILLEGAL_ARGUMENT_ERROR;
        return 0;
    }

    RegexMatcher *m = regexp->fMatcher;

    int32_t  srcIdx;
    if (m->fMatch) {

        srcIdx = m->fMatchEnd;
    } else {


        srcIdx = m->fLastMatchEnd;
        if (srcIdx == -1)  {


            srcIdx = 0;
        }
    }

    int32_t  destIdx     = 0;
    int32_t  destCap     = *destCapacity;
    UChar    *dest       = *destBuf;

    for (;;) {
        if (srcIdx == regexp->fTextLength) {
            break;
        }
        UChar c = regexp->fText[srcIdx];
        if (c == 0 && regexp->fTextLength == -1) {
            break;
        }
        if (destIdx < destCap) {
            dest[destIdx] = c;
        } else {


            if (regexp->fTextLength > 0) {
                destIdx += (regexp->fTextLength - srcIdx);
                break;
            }
        }
        srcIdx++;
        destIdx++;
    }


    if (destIdx < destCap) {
        dest[destIdx] = 0;
    } else  if (destIdx == destCap) {
        *status = U_STRING_NOT_TERMINATED_WARNING;
    } else {
        *status = U_BUFFER_OVERFLOW_ERROR;
    }


    if (destIdx < destCap) {
        *destBuf      += destIdx;
        *destCapacity -= destIdx;
    } else {
        *destBuf      += destCap;
        *destCapacity  = 0;
    }

    if (pendingBufferOverflow && U_SUCCESS(*status)) {
        *status = U_BUFFER_OVERFLOW_ERROR;
    }

    return destIdx;
}
