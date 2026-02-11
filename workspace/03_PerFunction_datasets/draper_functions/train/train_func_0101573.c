imparse_isatom(s)
const char *s;
{
    int len = 0;

    if (!*s) return 0;
    for (; *s; s++) {
	len++;
	if (*s & 0x80 || *s < 0x1f || *s == 0x7f ||
	    *s == ' ' || *s == '{' || *s == '(' || *s == ')' ||
	    *s == '\"' || *s == '%' || *s == '*' || *s == '\\') return 0;
    }
    if (len >= 1024) return 0;
    return 1;
}
