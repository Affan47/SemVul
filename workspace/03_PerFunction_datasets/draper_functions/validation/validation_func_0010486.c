do_sub(Term t, List lu)
	{
	if(is_label(t))
		{
		List l;
		l=lu;
		while(!is_empty_list(l))
			{
			Term t1;
			t1=ListFirst(l);
			if(CompoundArg1(t1)==t)
				return CopyTerm(CompoundArg2(t1));
			l=ListTail(l);
			}
		return t;
		}
	if(is_compound(t))
		{
		Term t1;
		int ac,i;
		t1=NewCompound(CompoundFunctor(t));
		ac=CompoundArity(t1);
		for(i=1;i<=ac;i++)
			SetCompoundArg(t1,i,do_sub(CompoundArgN(t,i),lu));
		return t1;
		}
	if(is_list(t))
		{
		List t1;
		t1=NewList();
		while(!is_empty_list(t))
			{
			t1=AppendLast(t1,do_sub(ListFirst(t),lu));
			t=ListTail(t);
			}
		return t1;
		}
	return CopyTerm(t);
	}
