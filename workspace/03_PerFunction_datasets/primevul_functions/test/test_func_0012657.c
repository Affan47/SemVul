shift_line(
    int	left,
    int	round,
    int	amount,
    int call_changed_bytes)
{
    int		count;
    int		i, j;
    int		sw_val = (int)get_sw_value_indent(curbuf);

    count = get_indent();

    if (round)
    {
	i = count / sw_val;
	j = count % sw_val;
	if (j && left)
	    --amount;
	if (left)
	{
	    i -= amount;
	    if (i < 0)
		i = 0;
	}
	else
	    i += amount;
	count = i * sw_val;
    }
    else
    {
	if (left)
	{
	    count -= sw_val * amount;
	    if (count < 0)
		count = 0;
	}
	else
	    count += sw_val * amount;
    }


    if (State & VREPLACE_FLAG)
	change_indent(INDENT_SET, count, FALSE, NUL, call_changed_bytes);
    else
	(void)set_indent(count, call_changed_bytes ? SIN_CHANGED : 0);
}
