uih_save_disable(struct uih_context *uih)
{
    if (uih->save) {
	last = 1;
	if (uih->savec->mode >= UIH_SAVEANIMATION)
	    uih_saveframe(uih);
	if (xio_close(uih->savec->file))
	    outputerror(uih);
	uih->save = 0;
	free(uih->savec->fcontext);
	tl_free_timer(uih->savec->timer);
	tl_free_timer(uih->savec->synctimer);
	free(uih->savec);
	uih_updatemenus(uih, "save");
    }
}
