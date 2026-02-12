spell_reload_one(
    char_u	*fname,
    int		added_word)
{
    slang_T	*slang;
    int		didit = FALSE;

    FOR_ALL_SPELL_LANGS(slang)
    {
	if (fullpathcmp(fname, slang->sl_fname, FALSE, TRUE) == FPC_SAME)
	{
	    slang_clear(slang);
	    if (spell_load_file(fname, NULL, slang, FALSE) == NULL)

		slang_clear(slang);
	    redraw_all_later(UPD_SOME_VALID);
	    didit = TRUE;
	}
    }


    if (added_word && !didit)
	did_set_spelllang(curwin);
}
