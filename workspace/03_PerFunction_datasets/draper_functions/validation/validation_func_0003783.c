DXInsert(Object o, Object add, char *name)
{
    if (!o || !add)
	DXErrorReturn(ERROR_MISSING_DATA, "null object");

    if (!tree_match(o, add, ARRAYREQ))
	DXErrorReturn(ERROR_BAD_CLASS, "object hierarchies don't match");

    return Field__Insert(o, add, name);
}
