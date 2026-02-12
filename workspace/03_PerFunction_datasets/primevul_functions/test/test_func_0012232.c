save_subexpr(regbehind_T *bp)
{
    int i;


    bp->save_need_clear_subexpr = rex.need_clear_subexpr;
    if (!rex.need_clear_subexpr)
    {
	for (i = 0; i < NSUBEXP; ++i)
	{
	    if (REG_MULTI)
	    {
		bp->save_start[i].se_u.pos = rex.reg_startpos[i];
		bp->save_end[i].se_u.pos = rex.reg_endpos[i];
	    }
	    else
	    {
		bp->save_start[i].se_u.ptr = rex.reg_startp[i];
		bp->save_end[i].se_u.ptr = rex.reg_endp[i];
	    }
	}
    }
}
