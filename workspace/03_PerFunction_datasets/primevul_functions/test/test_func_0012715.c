nfa_postprocess(nfa_regprog_T *prog)
{
    int i;
    int c;

    for (i = 0; i < prog->nstate; ++i)
    {
	c = prog->state[i].c;
	if (c == NFA_START_INVISIBLE
		|| c == NFA_START_INVISIBLE_NEG
		|| c == NFA_START_INVISIBLE_BEFORE
		|| c == NFA_START_INVISIBLE_BEFORE_NEG)
	{
	    int directly;


	    if (match_follows(prog->state[i].out1->out, 0))
		directly = TRUE;
	    else
	    {
		int ch_invisible = failure_chance(prog->state[i].out, 0);
		int ch_follows = failure_chance(prog->state[i].out1->out, 0);


		if (c == NFA_START_INVISIBLE_BEFORE
		     || c == NFA_START_INVISIBLE_BEFORE_NEG)
		{


		    if (prog->state[i].val <= 0 && ch_follows > 0)
			directly = FALSE;
		    else
			directly = ch_follows * 10 < ch_invisible;
		}
		else
		{


		    directly = ch_follows < ch_invisible;
		}
	    }
	    if (directly)

		++prog->state[i].c;
	}
    }
}
