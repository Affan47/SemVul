buf_setino(buf)
    buf_T	*buf;
{
    struct stat	st;

    if (buf->b_fname != NULL && mch_stat((char *)buf->b_fname, &st) >= 0)
    {
	buf->b_dev = st.st_dev;
	buf->b_ino = st.st_ino;
    }
    else
	buf->b_dev = -1;
}
