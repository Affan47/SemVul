lbr_chartabsize_adv(
    char_u	*line,
    char_u	**s,
    colnr_T	col)
{
    int		retval;

    retval = lbr_chartabsize(line, *s, col);
    MB_PTR_ADV(*s);
    return retval;
}
