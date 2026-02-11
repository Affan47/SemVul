find_tabpage(n)
    int		n;
{
    tabpage_T	*tp;
    int		i = 1;

    for (tp = first_tabpage; tp != NULL && i != n; tp = tp->tp_next)
	++i;
    return tp;
}
