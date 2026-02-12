forward_slash(char_u *fname)
{
    char_u	*p;

    if (path_with_url(fname))
	return;
    for (p = fname; *p != NUL; ++p)
# ifdef  FEAT_MBYTE

	if (enc_dbcs != 0 && (*mb_ptr2len)(p) > 1)
	    ++p;
	else
# endif
	if (*p == '\\')
	    *p = '/';
}
