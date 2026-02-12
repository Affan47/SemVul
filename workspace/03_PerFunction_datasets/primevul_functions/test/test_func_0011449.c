normal_cmd_get_count(
	cmdarg_T	*cap,
	int		c,
	int		toplevel UNUSED,
	int		set_prevcount UNUSED,
	int		*ctrl_w,
	int		*need_flushbuf UNUSED)
{
getcount:
    if (!(VIsual_active && VIsual_select))
    {


	while ((c >= '1' && c <= '9')
		|| (cap->count0 != 0 && (c == K_DEL || c == K_KDEL
			|| c == '0')))
	{
	    if (c == K_DEL || c == K_KDEL)
	    {
		cap->count0 /= 10;
#ifdef FEAT_CMDL_INFO
		del_from_showcmd(4);
#endif
	    }
	    else if (cap->count0 > 99999999L)
	    {
		cap->count0 = 999999999L;
	    }
	    else
	    {
		cap->count0 = cap->count0 * 10 + (c - '0');
	    }
#ifdef FEAT_EVAL


	    if (toplevel && readbuf1_empty())
		set_vcount_ca(cap, &set_prevcount);
#endif
	    if (*ctrl_w)
	    {
		++no_mapping;
		++allow_keys;
	    }
	    ++no_zero_mapping;
	    c = plain_vgetc();
	    LANGMAP_ADJUST(c, TRUE);
	    --no_zero_mapping;
	    if (*ctrl_w)
	    {
		--no_mapping;
		--allow_keys;
	    }
#ifdef FEAT_CMDL_INFO
	    *need_flushbuf |= add_to_showcmd(c);
#endif
	}


	if (c == Ctrl_W && !*ctrl_w && cap->oap->op_type == OP_NOP)
	{
	    *ctrl_w = TRUE;
	    cap->opcount = cap->count0;
	    cap->count0 = 0;
	    ++no_mapping;
	    ++allow_keys;
	    c = plain_vgetc();
	    LANGMAP_ADJUST(c, TRUE);
	    --no_mapping;
	    --allow_keys;
#ifdef FEAT_CMDL_INFO
	    *need_flushbuf |= add_to_showcmd(c);
#endif
	    goto getcount;
	}
    }

    if (c == K_CURSORHOLD)
    {


	cap->oap->prev_opcount = cap->opcount;
	cap->oap->prev_count0 = cap->count0;
    }
    else if (cap->opcount != 0)
    {


	if (cap->count0)
	{
	    if (cap->opcount >= 999999999L / cap->count0)
		cap->count0 = 999999999L;
	    else
		cap->count0 *= cap->opcount;
	}
	else
	    cap->count0 = cap->opcount;
    }


    cap->opcount = cap->count0;
    cap->count1 = (cap->count0 == 0 ? 1 : cap->count0);

#ifdef FEAT_EVAL


    if (toplevel && readbuf1_empty())
	set_vcount(cap->count0, cap->count1, set_prevcount);
#endif

    return c;
}
