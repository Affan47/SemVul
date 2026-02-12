regbranch(int *flagp)
{
    char_u	*ret;
    char_u	*chain = NULL;
    char_u	*latest;
    int		flags;

    *flagp = WORST | HASNL;

    ret = regnode(BRANCH);
    for (;;)
    {
	latest = regconcat(&flags);
	if (latest == NULL)
	    return NULL;


	*flagp |= flags & (HASWIDTH | SPSTART | HASLOOKBH);


	*flagp &= ~HASNL | (flags & HASNL);
	if (chain != NULL)
	    regtail(chain, latest);
	if (peekchr() != Magic('&'))
	    break;
	skipchr();
	regtail(latest, regnode(END));
	if (reg_toolong)
	    break;
	reginsert(MATCH, latest);
	chain = latest;
    }

    return ret;
}
