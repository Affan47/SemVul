finish_write_reg(
    int		name,
    yankreg_T	*old_y_previous,
    yankreg_T	*old_y_current)
{
# ifdef FEAT_CLIPBOARD

    may_set_selection();
# endif


    if (name != '"')
	y_previous = old_y_previous;
    y_current = old_y_current;
}
