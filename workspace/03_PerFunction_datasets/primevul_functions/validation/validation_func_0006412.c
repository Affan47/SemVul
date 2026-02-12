pum_wanted(void)
{

    if (vim_strchr(p_cot, 'm') == NULL)
	return FALSE;


    if (t_colors < 8
#ifdef FEAT_GUI
	    && !gui.in_use
#endif
	    )
	return FALSE;
    return TRUE;
}
