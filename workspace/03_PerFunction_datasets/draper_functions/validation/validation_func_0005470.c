byte2cells(b)
    int		b;
{
#ifdef FEAT_MBYTE
    if (enc_utf8 && b >= 0x80)
	return 0;
#endif
    return (chartab[b] & CT_CELL_MASK);
}
