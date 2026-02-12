_XQueryFont (
    register Display *dpy,
    Font fid,
    unsigned long seq)
{
    register XFontStruct *fs;
    unsigned long nbytes;
    unsigned long reply_left;
    xQueryFontReply reply;
    register xResourceReq *req;
    register _XExtension *ext;
    _XAsyncHandler async;
    _XAsyncErrorState async_state;

    if (seq) {
	async_state.min_sequence_number = seq;
	async_state.max_sequence_number = seq;
	async_state.error_code = BadName;
	async_state.major_opcode = X_OpenFont;
	async_state.minor_opcode = 0;
	async_state.error_count = 0;
	async.next = dpy->async_handlers;
	async.handler = _XAsyncErrorHandler;
	async.data = (XPointer)&async_state;
	dpy->async_handlers = &async;
    }
    GetResReq(QueryFont, fid, req);
    if (!_XReply (dpy, (xReply *) &reply,
       ((SIZEOF(xQueryFontReply) - SIZEOF(xReply)) >> 2), xFalse)) {
	if (seq)
	    DeqAsyncHandler(dpy, &async);
	return (XFontStruct *)NULL;
    }
    if (seq)
	DeqAsyncHandler(dpy, &async);
    reply_left = reply.length -
	((SIZEOF(xQueryFontReply) - SIZEOF(xReply)) >> 2);
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
    if (reply.nCharInfos > 0){

	if (reply.nCharInfos < (INT_MAX / sizeof(XCharStruct))) {
	    nbytes = reply.nCharInfos * SIZEOF(xCharInfo);
	    if ((nbytes >> 2) <= reply_left) {
		fs->per_char = Xmallocarray (reply.nCharInfos,
                                             sizeof(XCharStruct));
	    }
	}
	if (! fs->per_char) {
	    Xfree(fs->properties);
	    Xfree(fs);
	    _XEatDataWords(dpy, reply_left);
	    return (XFontStruct *)NULL;
	}

	_XRead16 (dpy, (char *)fs->per_char, nbytes);
    }


    for (ext = dpy->ext_procs; ext; ext = ext->next)
	if (ext->create_Font) (*ext->create_Font)(dpy, fs, &ext->codes);
    return fs;
}
