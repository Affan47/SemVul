empty_pattern_magic(char_u *p, size_t len, magic_T magic_val)
{

    while (len >= 2 && p[len - 2] == '\\'
                        && vim_strchr((char_u *)"mMvVcCZ", p[len - 1]) != NULL)
       len -= 2;


    return len == 0 || (len > 1
	    && ((p[len - 2] == '\\'
				 && p[len - 1] == '|' && magic_val == MAGIC_ON)
		|| (p[len - 2] != '\\'
			     && p[len - 1] == '|' && magic_val == MAGIC_ALL)));
}
