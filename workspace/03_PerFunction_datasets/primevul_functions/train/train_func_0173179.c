EndOfHeader(Sock *sockPtr)
{
    Request      *reqPtr;
    const char   *s;

    NS_NONNULL_ASSERT(sockPtr != NULL);

    reqPtr = sockPtr->reqPtr;
    assert(reqPtr != NULL);

    reqPtr->chunkStartOff = 0u;


    sockPtr->flags &= ~(NS_CONN_CONTINUE);
    s = Ns_SetIGet(reqPtr->headers, "expect");
    if (s != NULL) {
        if (*s == '1' && *(s+1) == '0' && *(s+2) == '0' && *(s+3) == '-') {
            char *dup = ns_strdup(s+4);

            Ns_StrToLower(dup);
            if (STREQ(dup, "continue")) {
                sockPtr->flags |= NS_CONN_CONTINUE;
            }
            ns_free(dup);
        }
    }


    sockPtr->flags &= ~(NS_CONN_ENTITYTOOLARGE);
    s = Ns_SetIGet(reqPtr->headers, "content-length");
    if (s == NULL) {
        s = Ns_SetIGet(reqPtr->headers, "Transfer-Encoding");

        if (s != NULL) {

            if (STREQ(s, "chunked") || STREQ(s, "Chunked")) {
                Tcl_WideInt expected;

                reqPtr->chunkStartOff = reqPtr->roff;
                reqPtr->chunkWriteOff = reqPtr->chunkStartOff;
                reqPtr->contentLength = 0u;


                s = Ns_SetIGet(reqPtr->headers, "X-Expected-Entity-Length");

                if ((s != NULL)
                    && (Ns_StrToWideInt(s, &expected) == NS_OK)
                    && (expected > 0) ) {
                    reqPtr->expectedLength = (size_t)expected;
                }
                s = NULL;
            }
        }
    }


    if (s != NULL) {
        Tcl_WideInt length;

        if ((Ns_StrToWideInt(s, &length) == NS_OK) && (length > 0)) {
            reqPtr->length = (size_t)length;


            if (reqPtr->length > (size_t)sockPtr->drvPtr->maxinput) {

                Ns_Log(Warning, "SockParse: request too large, length=%"
                       PRIdz ", maxinput=%" TCL_LL_MODIFIER "d",
                       reqPtr->length, sockPtr->drvPtr->maxinput);

                sockPtr->keep = NS_FALSE;
                sockPtr->flags |= NS_CONN_ENTITYTOOLARGE;

            }
            reqPtr->contentLength = (size_t)length;
        }
    }


    sockPtr->flags &= ~(NS_CONN_ZIPACCEPTED|NS_CONN_BROTLIACCEPTED);

    s = Ns_SetIGet(reqPtr->headers, "Accept-Encoding");
    if (s != NULL) {
        bool gzipAccept, brotliAccept;


        NsParseAcceptEncoding(reqPtr->request.version, s, &gzipAccept, &brotliAccept);
        if (gzipAccept || brotliAccept) {


            s = Ns_SetIGet(reqPtr->headers, "Range");
            if (s == NULL) {
                if (gzipAccept) {
                    sockPtr->flags |= NS_CONN_ZIPACCEPTED;
                }
                if (brotliAccept) {
                    sockPtr->flags |= NS_CONN_BROTLIACCEPTED;
                }
            }
        }
    }


    if (reqPtr->contentLength != 0u) {


        reqPtr->length = reqPtr->contentLength;
    }

    return reqPtr->roff;
}
