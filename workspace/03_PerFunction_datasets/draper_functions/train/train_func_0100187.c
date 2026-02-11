Perl_lex_grow_linestr(pTHX_ STRLEN len)
{
    SV *linestr;
    char *buf;
    STRLEN bufend_pos, bufptr_pos, oldbufptr_pos, oldoldbufptr_pos;
    STRLEN linestart_pos, last_uni_pos, last_lop_pos, re_eval_start_pos;
    linestr = PL_parser->linestr;
    buf = SvPVX(linestr);
    if (len <= SvLEN(linestr))
	return buf;
    bufend_pos = PL_parser->bufend - buf;
    bufptr_pos = PL_parser->bufptr - buf;
    oldbufptr_pos = PL_parser->oldbufptr - buf;
    oldoldbufptr_pos = PL_parser->oldoldbufptr - buf;
    linestart_pos = PL_parser->linestart - buf;
    last_uni_pos = PL_parser->last_uni ? PL_parser->last_uni - buf : 0;
    last_lop_pos = PL_parser->last_lop ? PL_parser->last_lop - buf : 0;
    re_eval_start_pos = PL_parser->lex_shared->re_eval_start ?
                            PL_parser->lex_shared->re_eval_start - buf : 0;

    buf = sv_grow(linestr, len);

    PL_parser->bufend = buf + bufend_pos;
    PL_parser->bufptr = buf + bufptr_pos;
    PL_parser->oldbufptr = buf + oldbufptr_pos;
    PL_parser->oldoldbufptr = buf + oldoldbufptr_pos;
    PL_parser->linestart = buf + linestart_pos;
    if (PL_parser->last_uni)
	PL_parser->last_uni = buf + last_uni_pos;
    if (PL_parser->last_lop)
	PL_parser->last_lop = buf + last_lop_pos;
    if (PL_parser->lex_shared->re_eval_start)
        PL_parser->lex_shared->re_eval_start  = buf + re_eval_start_pos;
    return buf;
}
