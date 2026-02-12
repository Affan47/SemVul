makeset(FILE *fd, int opt_flags, int local_only)
{
    struct vimoption	*p;
    char_u		*varp;
    char_u		*varp_fresh;
    char_u		*varp_local = NULL;
    char		*cmd;
    int			round;
    int			pri;


    for (pri = 1; pri >= 0; --pri)
    {
      for (p = &options[0]; !istermoption(p); p++)
	if (!(p->flags & P_NO_MKRC)
		&& !istermoption(p)
		&& ((pri == 1) == ((p->flags & P_PRI_MKRC) != 0)))
	{

	    if (p->indir == PV_NONE && !(opt_flags & OPT_GLOBAL))
		continue;


	    if ((opt_flags & OPT_GLOBAL) && (p->flags & P_NOGLOB))
		continue;


	    varp = get_varp_scope(p, opt_flags);
	    if ((opt_flags & OPT_GLOBAL) && optval_default(p, varp))
		continue;

	    round = 2;
	    if (p->indir != PV_NONE)
	    {
		if (p->var == VAR_WIN)
		{

		    if (!(opt_flags & OPT_LOCAL))
			continue;


		    if (!(opt_flags & OPT_GLOBAL) && !local_only)
		    {
			varp_fresh = get_varp_scope(p, OPT_GLOBAL);
			if (!optval_default(p, varp_fresh))
			{
			    round = 1;
			    varp_local = varp;
			    varp = varp_fresh;
			}
		    }
		}
	    }


	    for ( ; round <= 2; varp = varp_local, ++round)
	    {
		if (round == 1 || (opt_flags & OPT_GLOBAL))
		    cmd = "set";
		else
		    cmd = "setlocal";

		if (p->flags & P_BOOL)
		{
		    if (put_setbool(fd, cmd, p->fullname, *(int *)varp) == FAIL)
			return FAIL;
		}
		else if (p->flags & P_NUM)
		{
		    if (put_setnum(fd, cmd, p->fullname, (long *)varp) == FAIL)
			return FAIL;
		}
		else
		{
#if defined(FEAT_SYN_HL) || defined(FEAT_AUTOCMD)
		    int		do_endif = FALSE;


		    if (
# if defined(FEAT_SYN_HL)
			    p->indir == PV_SYN
#  if defined(FEAT_AUTOCMD)
			    ||
#  endif
# endif
# if defined(FEAT_AUTOCMD)
			    p->indir == PV_FT
# endif
			    )
		    {
			if (fprintf(fd, "if &%s != '%s'", p->fullname,
						       *(char_u **)(varp)) < 0
				|| put_eol(fd) < 0)
			    return FAIL;
			do_endif = TRUE;
		    }
#endif
		    if (put_setstring(fd, cmd, p->fullname, (char_u **)varp,
					  (p->flags & P_EXPAND) != 0) == FAIL)
			return FAIL;
#if defined(FEAT_SYN_HL) || defined(FEAT_AUTOCMD)
		    if (do_endif)
		    {
			if (put_line(fd, "endif") == FAIL)
			    return FAIL;
		    }
#endif
		}
	    }
	}
    }
    return OK;
}
