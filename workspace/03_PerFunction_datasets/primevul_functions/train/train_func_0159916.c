static rpmRC rpmpkgRead(rpmKeyring keyring, rpmVSFlags vsflags,
			FD_t fd,
			Header * hdrp, unsigned int *keyidp, char **msg)
{
    pgpDigParams sig = NULL;
    Header sigh = NULL;
    rpmTagVal sigtag;
    struct rpmtd_s sigtd;
    struct sigtInfo_s sinfo;
    Header h = NULL;
    rpmRC rc = RPMRC_FAIL;
    int leadtype = -1;
    headerGetFlags hgeflags = HEADERGET_DEFAULT;

    if (hdrp) *hdrp = NULL;

    rpmtdReset(&sigtd);

    if ((rc = rpmLeadRead(fd, NULL, &leadtype, msg)) != RPMRC_OK) {

	if (rc == RPMRC_NOTFOUND) {
	    *msg = _free(*msg);
	}
	goto exit;
    }


    rc = rpmReadSignature(fd, &sigh, RPMSIGTYPE_HEADERSIG, msg);

    if (rc != RPMRC_OK) {
	goto exit;
    }

#define	_chk(_mask, _tag) \
	(sigtag == 0 && !(vsflags & (_mask)) && headerIsEntry(sigh, (_tag)))


    sigtag = 0;
    if (_chk(RPMVSF_NODSAHEADER, RPMSIGTAG_DSA)) {
	sigtag = RPMSIGTAG_DSA;
    } else if (_chk(RPMVSF_NORSAHEADER, RPMSIGTAG_RSA)) {
	sigtag = RPMSIGTAG_RSA;
    } else if (_chk(RPMVSF_NOSHA1HEADER, RPMSIGTAG_SHA1)) {
	sigtag = RPMSIGTAG_SHA1;
    }


    h = NULL;

    rc = rpmpkgReadHeader(keyring, vsflags, fd, &h, msg);

    if (rc != RPMRC_OK || h == NULL) {
	goto exit;
    }


    if (sigtag == 0) {
	rc = RPMRC_OK;
	goto exit;
    }


    *msg = _free(*msg);


    if (!headerGet(sigh, sigtag, &sigtd, hgeflags)) {
	rc = RPMRC_FAIL;
	goto exit;
    }

    if (rpmSigInfoParse(&sigtd, "package", &sinfo, &sig, msg) == RPMRC_OK) {
	struct rpmtd_s utd;
	DIGEST_CTX ctx = rpmDigestInit(sinfo.hashalgo, RPMDIGEST_NONE);

	if (headerGet(h, RPMTAG_HEADERIMMUTABLE, &utd, hgeflags)) {
	    rpmDigestUpdate(ctx, rpm_header_magic, sizeof(rpm_header_magic));
	    rpmDigestUpdate(ctx, utd.data, utd.count);
	    rpmtdFreeData(&utd);
	}

	rc = rpmVerifySignature(keyring, &sigtd, sig, ctx, msg);

	rpmDigestFinal(ctx, NULL, NULL, 0);
    } else {
	rc = RPMRC_FAIL;
    }

exit:
    if (rc != RPMRC_FAIL && h != NULL && hdrp != NULL) {

	if (leadtype == RPMLEAD_SOURCE && headerIsSource(h)) {
	    if (!headerIsEntry(h, RPMTAG_SOURCEPACKAGE)) {
		uint32_t one = 1;
		headerPutUint32(h, RPMTAG_SOURCEPACKAGE, &one, 1);
	    }
	}


	if (!headerIsEntry(h, RPMTAG_SOURCEPACKAGE) && headerIsSource(h)) {
	    headerPutString(h, RPMTAG_SOURCERPM, "(none)");
	}


	if (!headerIsEntry(h, RPMTAG_HEADERIMMUTABLE))
	    headerConvert(h, HEADERCONV_RETROFIT_V3);
	else if (headerIsEntry(h, RPMTAG_OLDFILENAMES))
	    headerConvert(h, HEADERCONV_COMPRESSFILELIST);


	headerMergeLegacySigs(h, sigh);


	*hdrp = headerLink(h);

	if (keyidp)
	    *keyidp = getKeyid(sig);
    }
    rpmtdFreeData(&sigtd);
    h = headerFree(h);
    pgpDigParamsFree(sig);
    sigh = rpmFreeSignature(sigh);
    return rc;
}
