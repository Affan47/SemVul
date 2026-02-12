nfa_regbranch(void)
{
    int		old_post_pos;

    old_post_pos = (int)(post_ptr - post_start);


    if (nfa_regconcat() == FAIL)
	return FAIL;


    while (peekchr() == Magic('&'))
    {
	skipchr();

	if (old_post_pos == (int)(post_ptr - post_start))
	    EMIT(NFA_EMPTY);
	EMIT(NFA_NOPEN);
	EMIT(NFA_PREV_ATOM_NO_WIDTH);
	old_post_pos = (int)(post_ptr - post_start);
	if (nfa_regconcat() == FAIL)
	    return FAIL;

	if (old_post_pos == (int)(post_ptr - post_start))
	    EMIT(NFA_EMPTY);
	EMIT(NFA_CONCAT);
    }


    if (old_post_pos == (int)(post_ptr - post_start))
	EMIT(NFA_EMPTY);

    return OK;
}
