open_spellbuf()
{
    buf_T	*buf;

    buf = (buf_T *)alloc_clear(sizeof(buf_T));
    if (buf != NULL)
    {
	buf->b_spell = TRUE;
	buf->b_p_swf = TRUE;
#ifdef FEAT_CRYPT
	buf->b_p_key = empty_option;
#endif
	ml_open(buf);
	ml_open_file(buf);
    }
    return buf;
}
