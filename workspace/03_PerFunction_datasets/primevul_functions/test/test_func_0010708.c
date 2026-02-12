tputs(const char *string, int affcnt GCC_UNUSED, int (*outc) (int) GCC_UNUSED)

{
    if (profiling)
	xmits += strlen(string);
    else
	(void) fputs(_nc_visbuf(string), stdout);
    return (OK);
}
