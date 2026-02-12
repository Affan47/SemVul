post2nfa(int *postfix, int *end, int nfa_calc_size)
{
    int		*p;
    int		mopen;
    int		mclose;
    Frag_T	*stack = NULL;
    Frag_T	*stackp = NULL;
    Frag_T	*stack_end = NULL;
    Frag_T	e1;
    Frag_T	e2;
    Frag_T	e;
    nfa_state_T	*s;
    nfa_state_T	*s1;
    nfa_state_T	*matchstate;
    nfa_state_T	*ret = NULL;

    if (postfix == NULL)
	return NULL;

#define PUSH(s)	    st_push((s), &stackp, stack_end)
#define POP()	    st_pop(&stackp, stack);		\
		    if (stackp < stack)			\
		    {					\
			st_error(postfix, end, p);	\
			vim_free(stack);		\
			return NULL;			\
		    }

    if (nfa_calc_size == FALSE)
    {

	stack = ALLOC_MULT(Frag_T, nstate + 1);
	if (stack == NULL)
	    return NULL;
	stackp = stack;
	stack_end = stack + (nstate + 1);
    }

    for (p = postfix; p < end; ++p)
    {
	switch (*p)
	{
	case NFA_CONCAT:


	    if (nfa_calc_size == TRUE)
	    {

		break;
	    }
	    e2 = POP();
	    e1 = POP();
	    patch(e1.out, e2.start);
	    PUSH(frag(e1.start, e2.out));
	    break;

	case NFA_OR:

	    if (nfa_calc_size == TRUE)
	    {
		nstate++;
		break;
	    }
	    e2 = POP();
	    e1 = POP();
	    s = alloc_state(NFA_SPLIT, e1.start, e2.start);
	    if (s == NULL)
		goto theend;
	    PUSH(frag(s, append(e1.out, e2.out)));
	    break;

	case NFA_STAR:

	    if (nfa_calc_size == TRUE)
	    {
		nstate++;
		break;
	    }
	    e = POP();
	    s = alloc_state(NFA_SPLIT, e.start, NULL);
	    if (s == NULL)
		goto theend;
	    patch(e.out, s);
	    PUSH(frag(s, list1(&s->out1)));
	    break;

	case NFA_STAR_NONGREEDY:

	    if (nfa_calc_size == TRUE)
	    {
		nstate++;
		break;
	    }
	    e = POP();
	    s = alloc_state(NFA_SPLIT, NULL, e.start);
	    if (s == NULL)
		goto theend;
	    patch(e.out, s);
	    PUSH(frag(s, list1(&s->out)));
	    break;

	case NFA_QUEST:

	    if (nfa_calc_size == TRUE)
	    {
		nstate++;
		break;
	    }
	    e = POP();
	    s = alloc_state(NFA_SPLIT, e.start, NULL);
	    if (s == NULL)
		goto theend;
	    PUSH(frag(s, append(e.out, list1(&s->out1))));
	    break;

	case NFA_QUEST_NONGREEDY:

	    if (nfa_calc_size == TRUE)
	    {
		nstate++;
		break;
	    }
	    e = POP();
	    s = alloc_state(NFA_SPLIT, NULL, e.start);
	    if (s == NULL)
		goto theend;
	    PUSH(frag(s, append(e.out, list1(&s->out))));
	    break;

	case NFA_END_COLL:
	case NFA_END_NEG_COLL:


	    if (nfa_calc_size == TRUE)
	    {
		nstate++;
		break;
	    }
	    e = POP();
	    s = alloc_state(NFA_END_COLL, NULL, NULL);
	    if (s == NULL)
		goto theend;
	    patch(e.out, s);
	    e.start->out1 = s;
	    PUSH(frag(e.start, list1(&s->out)));
	    break;

	case NFA_RANGE:


	    if (nfa_calc_size == TRUE)
	    {

		break;
	    }
	    e2 = POP();
	    e1 = POP();
	    e2.start->val = e2.start->c;
	    e2.start->c = NFA_RANGE_MAX;
	    e1.start->val = e1.start->c;
	    e1.start->c = NFA_RANGE_MIN;
	    patch(e1.out, e2.start);
	    PUSH(frag(e1.start, e2.out));
	    break;

	case NFA_EMPTY:

	    if (nfa_calc_size == TRUE)
	    {
		nstate++;
		break;
	    }
	    s = alloc_state(NFA_EMPTY, NULL, NULL);
	    if (s == NULL)
		goto theend;
	    PUSH(frag(s, list1(&s->out)));
	    break;

	case NFA_OPT_CHARS:
	  {
	    int    n;


	    n = *++p;
	    if (nfa_calc_size == TRUE)
	    {
		nstate += n;
		break;
	    }
	    s = NULL;
	    e1.out = NULL;
	    s1 = NULL;
	    while (n-- > 0)
	    {
		e = POP();
		s = alloc_state(NFA_SPLIT, e.start, NULL);
		if (s == NULL)
		    goto theend;
		if (e1.out == NULL)
		    e1 = e;
		patch(e.out, s1);
		append(e1.out, list1(&s->out1));
		s1 = s;
	    }
	    PUSH(frag(s, e1.out));
	    break;
	  }

	case NFA_PREV_ATOM_NO_WIDTH:
	case NFA_PREV_ATOM_NO_WIDTH_NEG:
	case NFA_PREV_ATOM_JUST_BEFORE:
	case NFA_PREV_ATOM_JUST_BEFORE_NEG:
	case NFA_PREV_ATOM_LIKE_PATTERN:
	  {
	    int before = (*p == NFA_PREV_ATOM_JUST_BEFORE
				      || *p == NFA_PREV_ATOM_JUST_BEFORE_NEG);
	    int pattern = (*p == NFA_PREV_ATOM_LIKE_PATTERN);
	    int start_state;
	    int end_state;
	    int n = 0;
	    nfa_state_T *zend;
	    nfa_state_T *skip;

	    switch (*p)
	    {
		case NFA_PREV_ATOM_NO_WIDTH:
		    start_state = NFA_START_INVISIBLE;
		    end_state = NFA_END_INVISIBLE;
		    break;
		case NFA_PREV_ATOM_NO_WIDTH_NEG:
		    start_state = NFA_START_INVISIBLE_NEG;
		    end_state = NFA_END_INVISIBLE_NEG;
		    break;
		case NFA_PREV_ATOM_JUST_BEFORE:
		    start_state = NFA_START_INVISIBLE_BEFORE;
		    end_state = NFA_END_INVISIBLE;
		    break;
		case NFA_PREV_ATOM_JUST_BEFORE_NEG:
		    start_state = NFA_START_INVISIBLE_BEFORE_NEG;
		    end_state = NFA_END_INVISIBLE_NEG;
		    break;
		default:
		    start_state = NFA_START_PATTERN;
		    end_state = NFA_END_PATTERN;
		    break;
	    }

	    if (before)
		n = *++p;


	    if (nfa_calc_size == TRUE)
	    {
		nstate += pattern ? 4 : 2;
		break;
	    }
	    e = POP();
	    s1 = alloc_state(end_state, NULL, NULL);
	    if (s1 == NULL)
		goto theend;

	    s = alloc_state(start_state, e.start, s1);
	    if (s == NULL)
		goto theend;
	    if (pattern)
	    {

		skip = alloc_state(NFA_SKIP, NULL, NULL);
		if (skip == NULL)
		    goto theend;
		zend = alloc_state(NFA_ZEND, s1, NULL);
		if (zend == NULL)
		    goto theend;
		s1->out= skip;
		patch(e.out, zend);
		PUSH(frag(s, list1(&skip->out)));
	    }
	    else
	    {
		patch(e.out, s1);
		PUSH(frag(s, list1(&s1->out)));
		if (before)
		{
		    if (n <= 0)


			n = nfa_max_width(e.start, 0);
		    s->val = n;
		}
	    }
	    break;
	  }

	case NFA_COMPOSING:
#if 0

	    if (regflags & RF_ICOMBINE)
	    {

	    }
#endif


	case NFA_MOPEN:
	case NFA_MOPEN1:
	case NFA_MOPEN2:
	case NFA_MOPEN3:
	case NFA_MOPEN4:
	case NFA_MOPEN5:
	case NFA_MOPEN6:
	case NFA_MOPEN7:
	case NFA_MOPEN8:
	case NFA_MOPEN9:
#ifdef FEAT_SYN_HL
	case NFA_ZOPEN:
	case NFA_ZOPEN1:
	case NFA_ZOPEN2:
	case NFA_ZOPEN3:
	case NFA_ZOPEN4:
	case NFA_ZOPEN5:
	case NFA_ZOPEN6:
	case NFA_ZOPEN7:
	case NFA_ZOPEN8:
	case NFA_ZOPEN9:
#endif
	case NFA_NOPEN:
	    if (nfa_calc_size == TRUE)
	    {
		nstate += 2;
		break;
	    }

	    mopen = *p;
	    switch (*p)
	    {
		case NFA_NOPEN: mclose = NFA_NCLOSE; break;
#ifdef FEAT_SYN_HL
		case NFA_ZOPEN: mclose = NFA_ZCLOSE; break;
		case NFA_ZOPEN1: mclose = NFA_ZCLOSE1; break;
		case NFA_ZOPEN2: mclose = NFA_ZCLOSE2; break;
		case NFA_ZOPEN3: mclose = NFA_ZCLOSE3; break;
		case NFA_ZOPEN4: mclose = NFA_ZCLOSE4; break;
		case NFA_ZOPEN5: mclose = NFA_ZCLOSE5; break;
		case NFA_ZOPEN6: mclose = NFA_ZCLOSE6; break;
		case NFA_ZOPEN7: mclose = NFA_ZCLOSE7; break;
		case NFA_ZOPEN8: mclose = NFA_ZCLOSE8; break;
		case NFA_ZOPEN9: mclose = NFA_ZCLOSE9; break;
#endif
		case NFA_COMPOSING: mclose = NFA_END_COMPOSING; break;
		default:

		    mclose = *p + NSUBEXP;
		    break;
	    }


	    if (stackp == stack)
	    {
		s = alloc_state(mopen, NULL, NULL);
		if (s == NULL)
		    goto theend;
		s1 = alloc_state(mclose, NULL, NULL);
		if (s1 == NULL)
		    goto theend;
		patch(list1(&s->out), s1);
		PUSH(frag(s, list1(&s1->out)));
		break;
	    }


	    e = POP();
	    s = alloc_state(mopen, e.start, NULL);
	    if (s == NULL)
		goto theend;

	    s1 = alloc_state(mclose, NULL, NULL);
	    if (s1 == NULL)
		goto theend;
	    patch(e.out, s1);

	    if (mopen == NFA_COMPOSING)

		patch(list1(&s->out1), s1);

	    PUSH(frag(s, list1(&s1->out)));
	    break;

	case NFA_BACKREF1:
	case NFA_BACKREF2:
	case NFA_BACKREF3:
	case NFA_BACKREF4:
	case NFA_BACKREF5:
	case NFA_BACKREF6:
	case NFA_BACKREF7:
	case NFA_BACKREF8:
	case NFA_BACKREF9:
#ifdef FEAT_SYN_HL
	case NFA_ZREF1:
	case NFA_ZREF2:
	case NFA_ZREF3:
	case NFA_ZREF4:
	case NFA_ZREF5:
	case NFA_ZREF6:
	case NFA_ZREF7:
	case NFA_ZREF8:
	case NFA_ZREF9:
#endif
	    if (nfa_calc_size == TRUE)
	    {
		nstate += 2;
		break;
	    }
	    s = alloc_state(*p, NULL, NULL);
	    if (s == NULL)
		goto theend;
	    s1 = alloc_state(NFA_SKIP, NULL, NULL);
	    if (s1 == NULL)
		goto theend;
	    patch(list1(&s->out), s1);
	    PUSH(frag(s, list1(&s1->out)));
	    break;

	case NFA_LNUM:
	case NFA_LNUM_GT:
	case NFA_LNUM_LT:
	case NFA_VCOL:
	case NFA_VCOL_GT:
	case NFA_VCOL_LT:
	case NFA_COL:
	case NFA_COL_GT:
	case NFA_COL_LT:
	case NFA_MARK:
	case NFA_MARK_GT:
	case NFA_MARK_LT:
	  {
	    int n = *++p;

	    if (nfa_calc_size == TRUE)
	    {
		nstate += 1;
		break;
	    }
	    s = alloc_state(p[-1], NULL, NULL);
	    if (s == NULL)
		goto theend;
	    s->val = n;
	    PUSH(frag(s, list1(&s->out)));
	    break;
	  }

	case NFA_ZSTART:
	case NFA_ZEND:
	default:

	    if (nfa_calc_size == TRUE)
	    {
		nstate++;
		break;
	    }
	    s = alloc_state(*p, NULL, NULL);
	    if (s == NULL)
		goto theend;
	    PUSH(frag(s, list1(&s->out)));
	    break;

	}

    }

    if (nfa_calc_size == TRUE)
    {
	nstate++;
	goto theend;
    }

    e = POP();
    if (stackp != stack)
    {
	vim_free(stack);
	EMSG_RET_NULL(_("E875: (NFA regexp) (While converting from postfix to NFA), too many states left on stack"));
    }

    if (istate >= nstate)
    {
	vim_free(stack);
	EMSG_RET_NULL(_("E876: (NFA regexp) Not enough space to store the whole NFA "));
    }

    matchstate = &state_ptr[istate++];
    matchstate->c = NFA_MATCH;
    matchstate->out = matchstate->out1 = NULL;
    matchstate->id = 0;

    patch(e.out, matchstate);
    ret = e.start;

theend:
    vim_free(stack);
    return ret;

#undef POP1
#undef PUSH1
#undef POP2
#undef PUSH2
#undef POP
#undef PUSH
}
