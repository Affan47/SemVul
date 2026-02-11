xmlSecOpenSSLHmacExecute(xmlSecTransformPtr transform, int last, xmlSecTransformCtxPtr transformCtx) {
    xmlSecOpenSSLHmacCtxPtr ctx;
    xmlSecBufferPtr in, out;
    int ret;

    xmlSecAssert2(xmlSecTransformIsValid(transform), -1);
    xmlSecAssert2((transform->operation == xmlSecTransformOperationSign) || (transform->operation == xmlSecTransformOperationVerify), -1);
    xmlSecAssert2(xmlSecTransformCheckSize(transform, xmlSecOpenSSLHmacSize), -1);
    xmlSecAssert2(transformCtx != NULL, -1);

    in = &(transform->inBuf);
    out = &(transform->outBuf);

    ctx = xmlSecOpenSSLHmacGetCtx(transform);
    xmlSecAssert2(ctx != NULL, -1);
    xmlSecAssert2(ctx->ctxInitialized != 0, -1);

    if(transform->status == xmlSecTransformStatusNone) {

        transform->status = xmlSecTransformStatusWorking;
    }

    if(transform->status == xmlSecTransformStatusWorking) {
        xmlSecSize inSize;

        inSize = xmlSecBufferGetSize(in);
        if(inSize > 0) {
            HMAC_Update(&(ctx->hmacCtx), xmlSecBufferGetData(in), inSize);

            ret = xmlSecBufferRemoveHead(in, inSize);
            if(ret < 0) {
                xmlSecError(XMLSEC_ERRORS_HERE,
                            xmlSecErrorsSafeString(xmlSecTransformGetName(transform)),
                            "xmlSecBufferRemoveHead",
                            XMLSEC_ERRORS_R_XMLSEC_FAILED,
                            "size=%d", inSize);
                return(-1);
            }
        }

        if(last) {
            unsigned int dgstSize;

            HMAC_Final(&(ctx->hmacCtx), ctx->dgst, &dgstSize);
            xmlSecAssert2(dgstSize > 0, -1);


            if(ctx->dgstSize == 0) {
                ctx->dgstSize = XMLSEC_SIZE_BAD_CAST(dgstSize * 8);
            } else if(ctx->dgstSize <= XMLSEC_SIZE_BAD_CAST(8 * dgstSize)) {
                dgstSize = ((ctx->dgstSize + 7) / 8);
            } else {
                xmlSecError(XMLSEC_ERRORS_HERE,
                            xmlSecErrorsSafeString(xmlSecTransformGetName(transform)),
                            NULL,
                            XMLSEC_ERRORS_R_INVALID_SIZE,
                            "result-bits=%d;required-bits=%d",
                            8 * dgstSize, ctx->dgstSize);
                return(-1);
            }


            if(transform->operation == xmlSecTransformOperationSign) {
                ret = xmlSecBufferAppend(out, ctx->dgst, dgstSize);
                if(ret < 0) {
                    xmlSecError(XMLSEC_ERRORS_HERE,
                                xmlSecErrorsSafeString(xmlSecTransformGetName(transform)),
                                "xmlSecBufferAppend",
                                XMLSEC_ERRORS_R_XMLSEC_FAILED,
                                "size=%d", dgstSize);
                    return(-1);
                }
            }
            transform->status = xmlSecTransformStatusFinished;
        }
    } else if(transform->status == xmlSecTransformStatusFinished) {

        xmlSecAssert2(xmlSecBufferGetSize(in) == 0, -1);
    } else {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    xmlSecErrorsSafeString(xmlSecTransformGetName(transform)),
                    NULL,
                    XMLSEC_ERRORS_R_INVALID_STATUS,
                    "status=%d", transform->status);
        return(-1);
    }

    return(0);
}
