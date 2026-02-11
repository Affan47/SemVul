do_fileresearch(void)
{
    size_t begin = selected;
    bool didfind;

    search_init_globals();

    if (last_search[0] != '\0') {
#ifdef HAVE_REGEX_H

	if (ISSET(USE_REGEXP) && !regexp_init(last_search))
	    return;
#endif

	findnextfile_wrap_reset();
	didfind = findnextfile(FALSE, begin, answer);


	if (selected == begin && didfind) {


	    didfind = findnextfile(TRUE, begin, answer);
	    if (selected == begin && !didfind)
		statusbar(_("This is the only occurrence"));
	}
    } else
        statusbar(_("No current search pattern"));

    filesearch_abort();
}
