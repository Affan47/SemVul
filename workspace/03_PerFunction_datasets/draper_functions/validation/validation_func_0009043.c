P_packset(s)
register long *s;
{
    if (*s++)
        return *s;
    else
        return 0;
}
