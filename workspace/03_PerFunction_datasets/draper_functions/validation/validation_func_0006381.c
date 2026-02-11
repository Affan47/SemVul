get_arc(const unsigned char **bufp, const unsigned char *end,
        unsigned long *arc_out)
{
    const unsigned char *p = *bufp;
    unsigned long arc = 0, newval;

    if (p == end || !isdigit(*p))
        return 0;
    for (; p < end && isdigit(*p); p++) {
        newval = arc * 10 + (*p - '0');
        if (newval < arc)
            return 0;
        arc = newval;
    }
    while (p < end && (isspace(*p) || *p == '.'))
        p++;
    *bufp = p;
    *arc_out = arc;
    return 1;
}
