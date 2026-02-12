init_gui_options(void)
{


    if (!option_was_set((char_u *)"bg") && STRCMP(p_bg, gui_bg_default()) != 0)
    {
	set_option_value((char_u *)"bg", 0L, gui_bg_default(), 0);
	highlight_changed();
    }
}
