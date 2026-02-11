xmlSecTransformCreate(xmlSecTransformId id) {
    xmlSecTransformPtr transform;
    int ret;

    xmlSecAssert2(id != NULL, NULL);
    xmlSecAssert2(id->klassSize >= sizeof(xmlSecTransformKlass), NULL);
    xmlSecAssert2(id->objSize >= sizeof(xmlSecTransform), NULL);
    xmlSecAssert2(id->name != NULL, NULL);


    transform = (xmlSecTransformPtr)xmlMalloc(id->objSize);
    if(transform == NULL) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    NULL,
		    XMLSEC_ERRORS_R_MALLOC_FAILED,
		    "size=%d", id->objSize);
	return(NULL);
    }
    memset(transform, 0, id->objSize);
    transform->id = id;

    if(id->initialize != NULL) {
	ret = (id->initialize)(transform);
        if(ret < 0) {
	    xmlSecError(XMLSEC_ERRORS_HERE,
			xmlSecErrorsSafeString(xmlSecTransformGetName(transform)),
			"id->initialize",
			XMLSEC_ERRORS_R_XMLSEC_FAILED,
			XMLSEC_ERRORS_NO_MESSAGE);
	    xmlSecTransformDestroy(transform);
	    return(NULL);
	}
    }

    ret = xmlSecBufferInitialize(&(transform->inBuf), 0);
    if(ret < 0) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    xmlSecErrorsSafeString(xmlSecTransformGetName(transform)),
		    "xmlSecBufferInitialize",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    "size=%d", 0);
	xmlSecTransformDestroy(transform);
	return(NULL);
    }

    ret = xmlSecBufferInitialize(&(transform->outBuf), 0);
    if(ret < 0) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    xmlSecErrorsSafeString(xmlSecTransformGetName(transform)),
		    "xmlSecBufferInitialize",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    "size=%d", 0);
	xmlSecTransformDestroy(transform);
	return(NULL);
    }

    return(transform);
}
