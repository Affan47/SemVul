border_draw_title(
	FvwmWindow *fw, titlebar_descr *td)
{
	Pixmap p;

	if (td->layout.title_g.x < 0 || td->layout.title_g.y < 0)
	{
		return;
	}
	if (td->draw_rotation != ROTATION_0)
	{
		border_rotate_titlebar_descr(fw, td);
	}

	p = border_create_decor_pixmap(td->cd, &(td->layout.title_g));

#if 0
	fprintf(stderr,"drawing title\n");
#endif
	border_set_title_pixmap(fw, td, &p, FW_W_TITLE(fw));
	if (td->draw_rotation != ROTATION_0)
	{
		Pixmap tmp;

		tmp = CreateRotatedPixmap(
			dpy, p, td->layout.title_g.width,
			td->layout.title_g.height, Pdepth, Scr.BordersGC,
			td->draw_rotation);
		XFreePixmap(dpy, p);
		p = tmp;
		border_rotate_titlebar_descr(fw, td);
	}

	border_set_part_background(FW_W_TITLE(fw), p);
	XFreePixmap(dpy, p);
	if (td->tbstate.do_clear_title)
	{
		XClearWindow(dpy, FW_W_TITLE(fw));
	}

	return;
}
