emsg_text_too_long(void)
{
    emsg(_(e_resulting_text_too_long));
#ifdef FEAT_EVAL

    if (trylevel == 0)
#endif
	got_int = TRUE;
}
