ins_char(c)
    int		c;
{
#if defined(FEAT_MBYTE) || defined(PROTO)
    char_u	buf[MB_MAXBYTES + 1];
    int		n;

    n = (*mb_char2bytes)(c, buf);


    if (buf[0] == 0)
	buf[0] = '\n';

    ins_char_bytes(buf, n);
}
