normalize_ban (  char *src, char *dest, int destlen)
{

    if (strchr (src, '!'))
	return src;
    else if (invalid_nick (src))
    {
	char   *star;


	if (*src && src[strlen (src) - 1] == '.')
	    star = "*";
	else
	    star = "";
	snprintf (dest, destlen, "*!%s%s", src, star);
    }
    else
	snprintf (dest, destlen, "%s!*", src);
    return dest;
}
