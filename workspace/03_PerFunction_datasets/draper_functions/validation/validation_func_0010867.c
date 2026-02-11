border_get_frame_pixmap(
	common_decorations_type *cd, rectangle *frame_g)
{
	dynamic_common_decorations *dcd = &(cd->dynamic_cd);

	if (dcd->frame_pixmap != None)
	{

		fprintf(stderr, "Bad use of border_get_frame_pixmap!!\n");
		dcd->frame_pixmap = None;
	}

	if (cd->bg_border_cs < 0 || CSET_IS_TRANSPARENT(cd->bg_border_cs))
	{

	}
	else
	{
		dcd->frame_pixmap = CreateBackgroundPixmap(
			dpy, Scr.NoFocusWin, frame_g->width, frame_g->height,
			&Colorset[cd->bg_border_cs], Pdepth, Scr.BordersGC,
			False);
	}
	return;
}
