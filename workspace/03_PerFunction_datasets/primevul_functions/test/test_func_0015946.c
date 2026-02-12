home_replace_save(
    buf_T	*buf,
    char_u	*src)
{
    char_u	*dst;
    unsigned	len;

    len = 3;
    if (src != NULL)
	len += (unsigned)STRLEN(src);
    dst = alloc(len);
    if (dst != NULL)
	home_replace(buf, src, dst, len, TRUE);
    return dst;
}
