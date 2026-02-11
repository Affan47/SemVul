xmlSecXsltExecute(xmlSecTransformPtr transform, int last, xmlSecTransformCtxPtr transformCtx) {
    xmlSecXsltCtxPtr ctx;
    xmlSecBufferPtr in, out;
    xmlSecSize inSize, outSize;
    int ret;

    xmlSecAssert2(xmlSecTransformCheckId(transform, xmlSecTransformXsltId), -1);
    xmlSecAssert2(xmlSecTransformCheckSize(transform, xmlSecXsltSize), -1);
    xmlSecAssert2(transformCtx != NULL, -1);

    ctx = xmlSecXsltGetCtx(transform);
    xmlSecAssert2(ctx != NULL, -1);
    xmlSecAssert2(ctx->xslt != NULL, -1);

    in = &(transform->inBuf);
    out = &(transform->outBuf);
    inSize = xmlSecBufferGetSize(in);
    outSize = xmlSecBufferGetSize(out);

    if(transform->status == xmlSecTransformStatusNone) {
        transform->status = xmlSecTransformStatusWorking;
    }

    if((transform->status == xmlSecTransformStatusWorking) && (last == 0)) {

        xmlSecAssert2(outSize == 0, -1);

    } else  if((transform->status == xmlSecTransformStatusWorking) && (last != 0)) {
        xmlSecAssert2(outSize == 0, -1);

        ret = xmlSecXslProcess(ctx, in, out);
        if(ret < 0) {
            xmlSecError(XMLSEC_ERRORS_HERE,
                        xmlSecErrorsSafeString(xmlSecTransformGetName(transform)),
                        "xmlSecXslProcess",
                        XMLSEC_ERRORS_R_XMLSEC_FAILED,
                        XMLSEC_ERRORS_NO_MESSAGE);
            return(-1);
        }

        ret = xmlSecBufferRemoveHead(in, inSize);
        if(ret < 0) {
            xmlSecError(XMLSEC_ERRORS_HERE,
                        xmlSecErrorsSafeString(xmlSecTransformGetName(transform)),
                        "xmlSecBufferRemoveHead",
                        XMLSEC_ERRORS_R_XMLSEC_FAILED,
                        "size=%d", inSize);
            return(-1);
        }

        transform->status = xmlSecTransformStatusFinished;
    } else if(transform->status == xmlSecTransformStatusFinished) {

        xmlSecAssert2(inSize == 0, -1);
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
