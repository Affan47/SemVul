get_past_head(char_u *path)
{
    char_u  *retval;

#if defined(MSWIN)

    if (isalpha(path[0]) && path[1] == ':')
	retval = path + 2;
    else
	retval = path;
#else
# if defined(AMIGA)

    retval = vim_strchr(path, ':');
    if (retval == NULL)
	retval = path;
# else
    retval = path;
# endif
#endif

    while (vim_ispathsep(*retval))
	++retval;

    return retval;
}
