make_symbol(st)
object st;
{
	object x;
	int i;
	{BEGIN_NO_INTERRUPT;
	x = alloc_object(t_symbol);
	x->s.s_dbind = OBJNULL;
	x->s.s_sfdef = NOT_SPECIAL;
	x->s.s_fillp = st->st.st_fillp;
	x->s.s_self = NULL;
	x->s.s_gfdef = OBJNULL;
	x->s.s_plist = Cnil;
	x->s.s_hpack = Cnil;
	x->s.s_stype = (short)stp_ordinary;
	x->s.s_mflag = FALSE;
	vs_push(x);
	if (initflag==0 && st->st.st_self < heap_end)
		x->s.s_self = st->st.st_self;
	else {
		x->s.s_self = alloc_relblock(x->s.s_fillp);
		for (i = 0;  i < x->s.s_fillp;  i++)
			x->s.s_self[i] = st->st.st_self[i];
	}
	END_NO_INTERRUPT;}
	return(vs_pop);
}
