cstrncmp(char_u *s1, char_u *s2, int *n)
{
    int		result;

    if (!rex.reg_ic)
	result = STRNCMP(s1, s2, *n);
    else
	result = MB_STRNICMP(s1, s2, *n);


    if (result != 0 && enc_utf8 && rex.reg_icombine)
    {
	char_u	*str1, *str2;
	int	c1, c2, c11, c12;
	int	junk;


	str1 = s1;
	str2 = s2;
	c1 = c2 = 0;
	while ((int)(str1 - s1) < *n)
	{
	    c1 = mb_ptr2char_adv(&str1);
	    c2 = mb_ptr2char_adv(&str2);


	    if (c1 != c2 && (!rex.reg_ic || utf_fold(c1) != utf_fold(c2)))
	    {

		mb_decompose(c1, &c11, &junk, &junk);
		mb_decompose(c2, &c12, &junk, &junk);
		c1 = c11;
		c2 = c12;
		if (c11 != c12
			    && (!rex.reg_ic || utf_fold(c11) != utf_fold(c12)))
		    break;
	    }
	}
	result = c2 - c1;
	if (result == 0)
	    *n = (int)(str2 - s2);
    }

    return result;
}
