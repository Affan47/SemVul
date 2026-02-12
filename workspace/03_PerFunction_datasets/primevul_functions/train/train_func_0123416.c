tabline_height(void)
{
#ifdef FEAT_GUI_TABLINE

    if (gui_use_tabline())
	return 0;
#endif
    switch (p_stal)
    {
	case 0: return 0;
	case 1: return (first_tabpage->tp_next == NULL) ? 0 : 1;
    }
    return 1;
}
