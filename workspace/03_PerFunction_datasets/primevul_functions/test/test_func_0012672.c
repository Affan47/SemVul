pim_equal(nfa_pim_T *one, nfa_pim_T *two)
{
    int one_unused = (one == NULL || one->result == NFA_PIM_UNUSED);
    int two_unused = (two == NULL || two->result == NFA_PIM_UNUSED);

    if (one_unused)

	return two_unused;
    if (two_unused)

	return FALSE;

    if (one->state->id != two->state->id)
	return FALSE;

    if (REG_MULTI)
	return one->end.pos.lnum == two->end.pos.lnum
	    && one->end.pos.col == two->end.pos.col;
    return one->end.ptr == two->end.ptr;
}
