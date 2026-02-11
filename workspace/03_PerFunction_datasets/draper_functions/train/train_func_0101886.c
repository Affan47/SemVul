ajStrPasteMaxC (AjPStr* Pstr, ajlong pos, const char* txt,
		       size_t len)
{
    AjPStr thys;
    size_t ibegin;
    size_t iend;
    char* ptr1       = 0;
    const char* ptr2 = 0;
    size_t slen;
    size_t ilen;

    slen = strlen(txt);

    if(!*Pstr)
        *Pstr = ajStrNewResLenC("", 1, 0);
    else if((*Pstr)->Use > 1)
        ajStrGetuniqueStr(Pstr);

    thys = *Pstr;

    ibegin = ajCvtSposToPosStart(thys->Len, 0, pos);
    iend = ibegin + (size_t) len;

    if((iend  > thys->Len) || (len > slen) )
	return ajFalse;

    ptr1 = &thys->Ptr[ibegin];
    ptr2 = txt;

    for(ilen=(size_t )len; ilen > 0; --ilen)
	*ptr1++ = *ptr2++;

    return ajTrue;
}
