_XF86BigfontCodes (
    register Display *dpy)
{
    XEDataObject dpy_union;
    XExtData *pData;
    XF86BigfontCodes *pCodes;
    char *envval;

    dpy_union.display = dpy;


    pData = XFindOnExtensionList(XEHeadOfExtensionList(dpy_union),
				 XF86BigfontNumber);
    if (pData)
	return (XF86BigfontCodes *) pData->private_data;

    pData = Xmalloc(sizeof(XExtData) + sizeof(XF86BigfontCodes));
    if (!pData) {

	return (XF86BigfontCodes *) NULL;
    }


    envval = getenv("XF86BIGFONT_DISABLE");
    if (envval != NULL && envval[0] != '\0')
	pCodes = NULL;
    else {
	XExtCodes *codes = XInitExtension(dpy, XF86BIGFONTNAME);
	if (codes == NULL)
	    pCodes = NULL;
	else {
	    pCodes = (XF86BigfontCodes *) &pData[1];
	    pCodes->codes = codes;
	}
    }
    pData->number = XF86BigfontNumber;
    pData->private_data = (XPointer) pCodes;
    pData->free_private = _XF86BigfontFreeCodes;
    XAddToExtensionList(XEHeadOfExtensionList(dpy_union), pData);
    if (pCodes) {
	int result;


	xXF86BigfontQueryVersionReply reply;
	register xXF86BigfontQueryVersionReq *req;

	LockDisplay(dpy);

	GetReq(XF86BigfontQueryVersion, req);
	req->reqType = pCodes->codes->major_opcode;
	req->xf86bigfontReqType = X_XF86BigfontQueryVersion;

	result = _XReply (dpy, (xReply *) &reply,
		(SIZEOF(xXF86BigfontQueryVersionReply) - SIZEOF(xReply)) >> 2,
		xFalse);

	UnlockDisplay(dpy);
    	SyncHandle();

	if(!result)
	    goto ignore_extension;


	if (!(reply.majorVersion > 1
	      || (reply.majorVersion == 1 && reply.minorVersion >= 1)))
	    goto ignore_extension;

	pCodes->serverSignature = reply.signature;
	pCodes->serverCapabilities = reply.capabilities;
    }
    return pCodes;

  ignore_extension:


    pCodes = (XF86BigfontCodes *) NULL;
    pData->private_data = (XPointer) pCodes;
    return pCodes;
}
