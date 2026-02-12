reg_restore(regsave_T *save, garray_T *gap)
{
    if (REG_MULTI)
    {
	if (rex.lnum != save->rs_u.pos.lnum)
	{


	    rex.lnum = save->rs_u.pos.lnum;
	    rex.line = reg_getline(rex.lnum);
	}
	rex.input = rex.line + save->rs_u.pos.col;
    }
    else
	rex.input = save->rs_u.ptr;
    gap->ga_len = save->rs_len;
}
