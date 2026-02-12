can_be_compound(
    trystate_T	*sp,
    slang_T	*slang,
    char_u	*compflags,
    int		flag)
{


    if (!byte_in_str(sp->ts_complen == sp->ts_compsplit
		? slang->sl_compstartflags : slang->sl_compallflags, flag))
	return FALSE;


    if (slang->sl_comprules != NULL && sp->ts_complen > sp->ts_compsplit)
    {
	int v;

	compflags[sp->ts_complen] = flag;
	compflags[sp->ts_complen + 1] = NUL;
	v = match_compoundrule(slang, compflags + sp->ts_compsplit);
	compflags[sp->ts_complen] = NUL;
	return v;
    }

    return TRUE;
}
