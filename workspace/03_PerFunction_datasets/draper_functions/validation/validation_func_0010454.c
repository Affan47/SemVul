xmlSecNssKeyDataX509XmlRead(xmlSecKeyDataId id, xmlSecKeyPtr key,
				xmlNodePtr node, xmlSecKeyInfoCtxPtr keyInfoCtx) {
    xmlSecKeyDataPtr data;
    int ret;

    xmlSecAssert2(id == xmlSecNssKeyDataX509Id, -1);
    xmlSecAssert2(key != NULL, -1);
    xmlSecAssert2(node != NULL, -1);
    xmlSecAssert2(keyInfoCtx != NULL, -1);

    data = xmlSecKeyEnsureData(key, id);
    if(data == NULL) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    xmlSecErrorsSafeString(xmlSecKeyDataKlassGetName(id)),
		    "xmlSecKeyEnsureData",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    XMLSEC_ERRORS_NO_MESSAGE);
	return(-1);
    }

    ret = xmlSecNssX509DataNodeRead(data, node, keyInfoCtx);
    if(ret < 0) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    xmlSecErrorsSafeString(xmlSecKeyDataKlassGetName(id)),
		    "xmlSecNssX509DataNodeRead",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    XMLSEC_ERRORS_NO_MESSAGE);
	return(-1);
    }

    if((keyInfoCtx->flags & XMLSEC_KEYINFO_FLAGS_X509DATA_DONT_VERIFY_CERTS) == 0) {
        ret = xmlSecNssKeyDataX509VerifyAndExtractKey(data, key, keyInfoCtx);
	if(ret < 0) {
	    xmlSecError(XMLSEC_ERRORS_HERE,
		        xmlSecErrorsSafeString(xmlSecKeyDataKlassGetName(id)),
			"xmlSecNssKeyDataX509VerifyAndExtractKey",
		        XMLSEC_ERRORS_R_XMLSEC_FAILED,
			XMLSEC_ERRORS_NO_MESSAGE);
	    return(-1);
        }
    }
    return(0);
}
