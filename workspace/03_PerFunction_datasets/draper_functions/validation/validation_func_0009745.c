do_from_search(regex_t *re)
{
    ARTICLE	*art;

    art = next_in_order(NULL);
    if (!art) {
	set_no_art_message();
	return;
    }

    do {
	if (art->from && regexec(re, art->from, 0, NULL, 0) == 0)
	    break;
	art = next_in_order(art);
    } while (art);

    if (!art)
	set_message("No matches!", True);
    else {
	set_curr_art(art, True);
	if (global.mode == NewsModeThread)
	    setNewsModeThread();
	read_article(art, False, NULL, NULL);
    }
}
