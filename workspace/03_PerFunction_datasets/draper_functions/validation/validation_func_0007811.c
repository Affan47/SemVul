do_uncut_text(void)
{
    assert(openfile->current != NULL && openfile->current->data != NULL);


    if (cutbuffer == NULL)
	return;

#ifndef NANO_TINY
     update_undo(UNCUT);
#endif


    copy_from_filestruct(cutbuffer, cutbottom);


    openfile->placewewant = xplustabs();


    set_modified();


    edit_refresh_needed = TRUE;

#ifdef ENABLE_COLOR
    reset_multis(openfile->current, FALSE);
#endif

#ifdef DEBUG
    dump_filestruct_reverse();
#endif
}
