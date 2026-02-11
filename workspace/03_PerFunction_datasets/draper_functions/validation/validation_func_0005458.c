_nc_get_type(char *name)
{
#if NO_LEAKS
    if (name == 0 && TermType != 0) {
	FreeAndNull(TermType);
	return;
    }
#endif
    if (name != 0)
	strcpy(name, TermType != 0 ? TermType : "");
}
