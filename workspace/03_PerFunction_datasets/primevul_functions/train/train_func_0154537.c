didset_options2(void)
{

    (void)highlight_changed();


    check_opt_wim();

    (void)set_chars_option(&p_lcs);
#if defined(FEAT_WINDOWS) || defined(FEAT_FOLDING)

    (void)set_chars_option(&p_fcs);
#endif

#ifdef FEAT_CLIPBOARD

    (void)check_clipboard_option();
#endif
}
