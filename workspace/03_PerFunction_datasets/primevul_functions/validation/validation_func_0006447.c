ins_compl_upd_pum(void)
{
    int		h;

    if (compl_match_array == NULL)
	return;

    h = curwin->w_cline_height;

    pum_call_update_screen();
    if (h != curwin->w_cline_height)
	ins_compl_del_pum();
}
