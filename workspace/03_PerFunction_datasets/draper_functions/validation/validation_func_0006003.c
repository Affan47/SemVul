at_number(const char *cp)
{
    size_t n = strspn(cp, NUMERIC);
    if (n < 1)
	return 0;
    return (cp + n);
}
