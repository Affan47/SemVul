after_updating_screen(int may_resize_shell UNUSED)
{
    updating_screen = FALSE;
#ifdef FEAT_GUI
    if (may_resize_shell)
	gui_may_resize_shell();
#endif
#ifdef FEAT_TERMINAL
    term_check_channel_closed_recently();
#endif

#ifdef HAVE_DROP_FILE


    handle_any_postponed_drop();
#endif
}
