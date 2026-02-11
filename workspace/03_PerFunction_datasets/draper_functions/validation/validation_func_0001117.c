setinvalids(StackInfo *si, Field f)
{
    InvalidComponentHandle ich;

    if (ISSET(si->stackflags, INVPOS))
	ich = DXCreateInvalidComponentHandle((Object)f,
					     NULL, "invalid positions");
    else
	ich = DXCreateInvalidComponentHandle((Object)f,
					     NULL, "invalid connections");

    if (!ich)
	return NULL;

    if (!DXSaveInvalidComponent(f, ich))
	return NULL;

    if (!DXFreeInvalidComponentHandle(ich))
	return NULL;

    return f;
}
