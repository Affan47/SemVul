match_delete(wp, id, perr)
    win_T	*wp;
    int		id;
    int		perr;
{
    matchitem_T *cur = wp->w_match_head;
    matchitem_T *prev = cur;

    if (id < 1)
    {
	if (perr == TRUE)
	    EMSGN("E802: Invalid ID: %ld (must be greater than or equal to 1)",
									  id);
	return -1;
    }
    while (cur != NULL && cur->id != id)
    {
	prev = cur;
	cur = cur->next;
    }
    if (cur == NULL)
    {
	if (perr == TRUE)
	    EMSGN("E803: ID not found: %ld", id);
	return -1;
    }
    if (cur == prev)
	wp->w_match_head = cur->next;
    else
	prev->next = cur->next;
    vim_regfree(cur->match.regprog);
    vim_free(cur->pattern);
    vim_free(cur);
    redraw_later(SOME_VALID);
    return 0;
}
