nv_search(cmdarg_T *cap)
{
    oparg_T	*oap = cap->oap;
    pos_T	save_cursor = curwin->w_cursor;

    if (cap->cmdchar == '?' && cap->oap->op_type == OP_ROT13)
    {

	cap->cmdchar = 'g';
	cap->nchar = '?';
	nv_operator(cap);
	return;
    }


    cap->searchbuf = getcmdline(cap->cmdchar, cap->count1, 0, 0);

    if (cap->searchbuf == NULL)
    {
	clearop(oap);
	return;
    }

    (void)normal_search(cap, cap->cmdchar, cap->searchbuf,
			(cap->arg || !EQUAL_POS(save_cursor, curwin->w_cursor))
						      ? 0 : SEARCH_MARK, NULL);
}
