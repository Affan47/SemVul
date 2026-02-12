term_settitle(char_u *title)
{
    MAY_WANT_TO_LOG_THIS;


    OUT_STR(tgoto((char *)T_TS, 0, 0));
    out_str_nf(title);
    out_str(T_FS);
    out_flush();
}
