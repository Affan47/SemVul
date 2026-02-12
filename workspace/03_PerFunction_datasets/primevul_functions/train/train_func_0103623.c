_XF86BigfontQueryFont (
    register Display *dpy,
    XF86BigfontCodes *extcodes,
    Font fid,
    unsigned long seq)
{
    register XFontStruct *fs;
    unsigned long nbytes;
    unsigned long reply_left;
    xXF86BigfontQueryFontReply reply;
    register xXF86BigfontQueryFontReq *req;
    register _XExtension *ext;
    _XAsyncHandler async1;
    _XAsyncErrorState async1_state;
    _XAsyncHandler async2;
    _XAsyncErrorState async2_state;

    if (seq) {
	async1_state.min_sequence_number = seq;
	async1_state.max_sequence_number = seq;
	async1_state.error_code = BadName;
	async1_state.major_opcode = X_OpenFont;
	async1_state.minor_opcode = 0;
	async1_state.error_count = 0;
	async1.next = dpy->async_handlers;
	async1.handler = _XAsyncErrorHandler;
	async1.data = (XPointer)&async1_state;
	dpy->async_handlers = &async1;
    }

    GetReq(XF86BigfontQueryFont, req);
    req->reqType = extcodes->codes->major_opcode;
    req->xf86bigfontReqType = X_XF86BigfontQueryFont;
    req->id = fid;
    req->flags = (extcodes->serverCapabilities & XF86Bigfont_CAP_LocalShm
		  ? XF86Bigfont_FLAGS_Shm : 0);


    async2_state.min_sequence_number = dpy->request;
    async2_state.max_sequence_number = dpy->request;
    async2_state.error_code = BadFont;
    async2_state.major_opcode = extcodes->codes->major_opcode;
    async2_state.minor_opcode = X_XF86BigfontQueryFont;
    async2_state.error_count = 0;
    async2.next = dpy->async_handlers;
    async2.handler = _XAsyncErrorHandler;
    async2.data = (XPointer)&async2_state;
    dpy->async_handlers = &async2;

    if (!_XReply (dpy, (xReply *) &reply,
       ((SIZEOF(xXF86BigfontQueryFontReply) - SIZEOF(xReply)) >> 2), xFalse)) {
	DeqAsyncHandler(dpy, &async2);
	if (seq)
	    DeqAsyncHandler(dpy, &async1);
	return (XFontStruct *)NULL;
    }
    DeqAsyncHandler(dpy, &async2);
    if (seq)
	DeqAsyncHandler(dpy, &async1);
    reply_left = reply.length -
	((SIZEOF(xXF86BigfontQueryFontReply) - SIZEOF(xReply)) >> 2);
    if (! (fs = Xmalloc (sizeof (XFontStruct)))) {
	_XEatDataWords(dpy, reply_left);
	return (XFontStruct *)NULL;
    }
    fs->ext_data 		= NULL;
    fs->fid 			= fid;
    fs->direction 		= reply.drawDirection;
    fs->min_char_or_byte2	= reply.minCharOrByte2;
    fs->max_char_or_byte2 	= reply.maxCharOrByte2;
    fs->min_byte1 		= reply.minByte1;
    fs->max_byte1 		= reply.maxByte1;
    fs->default_char 		= reply.defaultChar;
    fs->all_chars_exist 	= reply.allCharsExist;
    fs->ascent 			= cvtINT16toInt (reply.fontAscent);
    fs->descent 		= cvtINT16toInt (reply.fontDescent);


    fs->min_bounds = * (XCharStruct *) &reply.minBounds;
    fs->max_bounds = * (XCharStruct *) &reply.maxBounds;

    fs->n_properties = reply.nFontProps;


    fs->properties = NULL;
    if (fs->n_properties > 0) {

	nbytes = reply.nFontProps * SIZEOF(xFontProp);
	if ((nbytes >> 2) <= reply_left) {
	    fs->properties = Xmallocarray (reply.nFontProps,
                                           sizeof(XFontProp));
	}
	if (! fs->properties) {
	    Xfree(fs);
	    _XEatDataWords(dpy, reply_left);
	    return (XFontStruct *)NULL;
	}
	_XRead32 (dpy, (long *)fs->properties, nbytes);
	reply_left -= (nbytes >> 2);
    }

    fs->per_char = NULL;
#ifndef LONG64


    if (reply.nUniqCharInfos > ((ULONG_MAX / 2) / SIZEOF(xCharInfo)) ||
	reply.nCharInfos > ((ULONG_MAX / 2) / sizeof(CARD16))) {
	Xfree(fs->properties);
	Xfree(fs);
	_XEatDataWords(dpy, reply_left);
	return (XFontStruct *)NULL;
    }
#endif
    if (reply.nCharInfos > 0) {

	if (reply.shmid == (CARD32)(-1)) {
	    xCharInfo* pUniqCI;
	    CARD16* pIndex2UniqIndex;
	    int i;

	    nbytes = reply.nUniqCharInfos * SIZEOF(xCharInfo)
	             + (reply.nCharInfos+1)/2 * 2 * sizeof(CARD16);
	    pUniqCI = Xmalloc (nbytes);
	    if (!pUniqCI) {
		Xfree(fs->properties);
		Xfree(fs);
		_XEatDataWords(dpy, reply_left);
		return (XFontStruct *)NULL;
	    }
	    if (! (fs->per_char = Xmallocarray (reply.nCharInfos,
                                                sizeof(XCharStruct)))) {
		Xfree(pUniqCI);
		Xfree(fs->properties);
		Xfree(fs);
		_XEatDataWords(dpy, reply_left);
		return (XFontStruct *)NULL;
	    }
	    _XRead16 (dpy, (char *) pUniqCI, nbytes);
	    pIndex2UniqIndex = (CARD16*) (pUniqCI + reply.nUniqCharInfos);
	    for (i = 0; i < reply.nCharInfos; i++) {
		if (pIndex2UniqIndex[i] >= reply.nUniqCharInfos) {
		    fprintf(stderr, "_XF86BigfontQueryFont: server returned wrong data\n");
		    Xfree(pUniqCI);
		    Xfree(fs->properties);
		    Xfree(fs);
		    return (XFontStruct *)NULL;
		}

		fs->per_char[i] = * (XCharStruct *) &pUniqCI[pIndex2UniqIndex[i]];
	    }
	    Xfree(pUniqCI);
	} else {
#ifdef HAS_SHM
	    XExtData *pData;
	    XEDataObject fs_union;
	    char *addr;

	    pData = Xmalloc(sizeof(XExtData));
	    if (!pData) {
		Xfree(fs->properties);
		Xfree(fs);
		return (XFontStruct *)NULL;
	    }


	    if ((addr = shmat(reply.shmid, NULL, SHM_RDONLY)) == (char *)-1) {
		if (extcodes->serverCapabilities & CAP_VerifiedLocal)
		    fprintf(stderr, "_XF86BigfontQueryFont: could not attach shm segment\n");
	        Xfree(pData);
	        Xfree(fs->properties);
	        Xfree(fs);

		extcodes->serverCapabilities &= ~ XF86Bigfont_CAP_LocalShm;
	        return (XFontStruct *)NULL;
	    }

	    if (!(extcodes->serverCapabilities & CAP_VerifiedLocal)) {
		struct shmid_ds buf;
		if (!(shmctl(reply.shmid, IPC_STAT, &buf) >= 0
		      && reply.nCharInfos < (INT_MAX / sizeof(XCharStruct))
		      && buf.shm_segsz >= reply.shmsegoffset + reply.nCharInfos * sizeof(XCharStruct) + sizeof(CARD32)
		      && *(CARD32 *)(addr + reply.shmsegoffset + reply.nCharInfos * sizeof(XCharStruct)) == extcodes->serverSignature)) {
		    shmdt(addr);
		    Xfree(pData);
		    Xfree(fs->properties);
		    Xfree(fs);

		    extcodes->serverCapabilities &= ~ XF86Bigfont_CAP_LocalShm;
		    return (XFontStruct *)NULL;
		}
		extcodes->serverCapabilities |= CAP_VerifiedLocal;
	    }

	    pData->number = XF86BigfontNumber;
	    pData->private_data = (XPointer) addr;
	    pData->free_private = _XF86BigfontFreeNop;
	    fs_union.font = fs;
	    XAddToExtensionList(XEHeadOfExtensionList(fs_union), pData);

	    fs->per_char = (XCharStruct *) (addr + reply.shmsegoffset);
#else
	    fprintf(stderr, "_XF86BigfontQueryFont: try recompiling libX11 with HasShm, Xserver has shm support\n");
	    if (fs->properties) Xfree(fs->properties);
	    Xfree(fs);

	    extcodes->serverCapabilities &= ~ XF86Bigfont_CAP_LocalShm;
	    return (XFontStruct *)NULL;
#endif
	}
    }


    for (ext = dpy->ext_procs; ext; ext = ext->next)
	if (ext->create_Font) (*ext->create_Font)(dpy, fs, &ext->codes);
    return fs;
}
