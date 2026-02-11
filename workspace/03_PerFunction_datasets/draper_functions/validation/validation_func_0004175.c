ajCharSuffixS(const char* txt, const AjPStr str)
{
    size_t jlen;
    size_t jstart;

    if(!txt)
	return ajFalse;

    if(!str)
	return ajFalse;

    jlen   = strlen(txt);
    jstart = jlen - str->Len;

    if(str->Len > jlen)
	return ajFalse;

    if(strncmp(&txt[jstart], MAJSTRGETPTR(str), str->Len))

	return ajFalse;

    return ajTrue;
}
