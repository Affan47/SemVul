nfa_save_listids(nfa_regprog_T *prog, int *list)
{
    int		    i;
    nfa_state_T	    *p;


    p = &prog->state[0];
    for (i = prog->nstate; --i >= 0; )
    {
	list[i] = p->lastlist[1];
	p->lastlist[1] = 0;
	++p;
    }
}
