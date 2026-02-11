ifFilled(node_t * n)
{
    char *style, *p, **pp;
    int r = 0;
    style = late_nnstring(n, N_style, "");
    if (style[0]) {
        pp = parse_style(style);
        while ((p = *pp)) {
            if (strcmp(p, "filled") == 0)
                r = 1;
            pp++;
        }
    }
    return r;
}
