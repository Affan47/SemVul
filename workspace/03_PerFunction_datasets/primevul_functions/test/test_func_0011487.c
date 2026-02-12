nv_gd(
    oparg_T	*oap,
    int		nchar,
    int		thisblock)
{
    int		len;
    char_u	*ptr;

    if ((len = find_ident_under_cursor(&ptr, FIND_IDENT)) == 0
	    || find_decl(ptr, len, nchar == 'd', thisblock, SEARCH_START)
								       == FAIL)
    {
	clearopbeep(oap);
    }
    else
    {
#ifdef FEAT_FOLDING
	if ((fdo_flags & FDO_SEARCH) && KeyTyped && oap->op_type == OP_NOP)
	    foldOpenCursor();
#endif

	if (messaging() && !msg_silent && !shortmess(SHM_SEARCHCOUNT))
	    clear_cmdline = TRUE;
    }
}
