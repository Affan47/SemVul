state_in_list(
    nfa_list_T		*l,
    nfa_state_T		*state,
    regsubs_T		*subs)
{
    if (state->lastlist[nfa_ll_index] == l->id)
    {
	if (!rex.nfa_has_backref || has_state_with_pos(l, state, subs, NULL))
	    return TRUE;
    }
    return FALSE;
}
