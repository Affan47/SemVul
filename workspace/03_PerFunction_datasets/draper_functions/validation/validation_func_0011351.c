genTokenPointers( Junction *q )
#else
genTokenPointers( q )
Junction *q;
#endif
{


	int first=1, t=0;
	set a;
	tokensRefdInBlock = q->tokrefs;

	if ( set_deg(q->tokrefs) == 0 ) return;
	a = set_dup(q->tokrefs);
	gen("ANTLRTokenPtr ");
	for (; !set_nil(a); set_rm(t, a))
	{
		t = set_int(a);
		if ( first ) first = 0;
		else _gen(",");
		if ( !DontCopyTokens ) _gen2("_tv%d%d,", BlkLevel, t);
		_gen2("_t%d%d", BlkLevel, t);
		if ( !DontCopyTokens ) {_gen2("= &_tv%d%d", BlkLevel, t);}
		else _gen("=NULL");
	}
	_gen(";\n");
	set_free(a);
}
