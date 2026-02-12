immedhook(ENTRY * ep GCC_UNUSED)

{
#if !HAVE_BIG_CORE


    if (ep->nuses == 0) {
	int oldline = _nc_curr_line;

	write_it(ep);
	_nc_curr_line = oldline;
	free(ep->tterm.str_table);
	return (TRUE);
    }
#endif
    return (FALSE);
}
