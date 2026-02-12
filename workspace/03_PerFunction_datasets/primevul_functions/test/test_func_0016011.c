ptr2cells(char_u *p)
{

    if (enc_utf8 && *p >= 0x80)
	return utf_ptr2cells(p);

    return (g_chartab[*p] & CT_CELL_MASK);
}
