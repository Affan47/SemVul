valid_word_prefix(
    int		totprefcnt,
    int		arridx,
    int		flags,
    char_u	*word,
    slang_T	*slang,
    int		cond_req)
{
    int		prefcnt;
    int		pidx;
    regprog_T	**rp;
    int		prefid;

    prefid = (unsigned)flags >> 24;
    for (prefcnt = totprefcnt - 1; prefcnt >= 0; --prefcnt)
    {
	pidx = slang->sl_pidxs[arridx + prefcnt];


	if (prefid != (pidx & 0xff))
	    continue;


	if ((flags & WF_HAS_AFF) && (pidx & WF_PFX_NC))
	    continue;


	rp = &slang->sl_prefprog[((unsigned)pidx >> 8) & 0xffff];
	if (*rp != NULL)
	{
	    if (!vim_regexec_prog(rp, FALSE, word, 0))
		continue;
	}
	else if (cond_req)
	    continue;


	return pidx;
    }
    return 0;
}
