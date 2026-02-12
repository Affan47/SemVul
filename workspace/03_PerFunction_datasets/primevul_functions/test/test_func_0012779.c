find_cmdline_var(char_u *src, int *usedlen)
{
    int		len;
    int		i;
    static char *(spec_str[]) = {
		    "%",
#define SPEC_PERC   0
		    "#",
#define SPEC_HASH   (SPEC_PERC + 1)
		    "<cword>",
#define SPEC_CWORD  (SPEC_HASH + 1)
		    "<cWORD>",
#define SPEC_CCWORD (SPEC_CWORD + 1)
		    "<cexpr>",
#define SPEC_CEXPR  (SPEC_CCWORD + 1)
		    "<cfile>",
#define SPEC_CFILE  (SPEC_CEXPR + 1)
		    "<sfile>",
#define SPEC_SFILE  (SPEC_CFILE + 1)
		    "<slnum>",
#define SPEC_SLNUM  (SPEC_SFILE + 1)
		    "<stack>",
#define SPEC_STACK  (SPEC_SLNUM + 1)
		    "<script>",
#define SPEC_SCRIPT (SPEC_STACK + 1)
		    "<afile>",
#define SPEC_AFILE  (SPEC_SCRIPT + 1)
		    "<abuf>",
#define SPEC_ABUF   (SPEC_AFILE + 1)
		    "<amatch>",
#define SPEC_AMATCH (SPEC_ABUF + 1)
		    "<sflnum>",
#define SPEC_SFLNUM  (SPEC_AMATCH + 1)
		    "<SID>",
#define SPEC_SID  (SPEC_SFLNUM + 1)
#ifdef FEAT_CLIENTSERVER
		    "<client>"
# define SPEC_CLIENT (SPEC_SID + 1)
#endif
    };

    for (i = 0; i < (int)ARRAY_LENGTH(spec_str); ++i)
    {
	len = (int)STRLEN(spec_str[i]);
	if (STRNCMP(src, spec_str[i], len) == 0)
	{
	    *usedlen = len;
	    return i;
	}
    }
    return -1;
}
