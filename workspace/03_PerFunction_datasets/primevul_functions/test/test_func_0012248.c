seen_endbrace(int refnum)
{
    if (!had_endbrace[refnum])
    {
	char_u *p;


	for (p = regparse; *p != NUL; ++p)
	    if (p[0] == '@' && p[1] == '<' && (p[2] == '!' || p[2] == '='))
		break;
	if (*p == NUL)
	{
	    emsg(_(e_illegal_back_reference));
	    rc_did_emsg = TRUE;
	    return FALSE;
	}
    }
    return TRUE;
}
