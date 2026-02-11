show_pango_rectangle (CellEdit *edit,
                      PangoRectangle rect)
{
	gint x1 = rect.x / PANGO_SCALE;
	gint x2 = (rect.x + rect.width) / PANGO_SCALE;
#if 0
	gint y1 = rect.y / PANGO_SCALE;
	gint y2 = (rect.y + rect.height) / PANGO_SCALE;
#endif

	gint new_xofs_edit = edit->xofs_edit;
	gint new_yofs_edit = edit->yofs_edit;

	if (x1 < new_xofs_edit)
		new_xofs_edit = x1;
	if (2 + x2 - edit->cell_width > new_xofs_edit)
		new_xofs_edit = 2 + x2 - edit->cell_width;
	if (new_xofs_edit < 0)
		new_xofs_edit = 0;

#if 0
	if (y1 < new_yofs_edit)
		new_yofs_edit = y1;
	if (2 + y2 - edit->cell_height > new_yofs_edit)
		new_yofs_edit = 2 + y2 - edit->cell_height;
	if (new_yofs_edit < 0)
		new_yofs_edit = 0;
#endif

	if (new_xofs_edit != edit->xofs_edit ||
	    new_yofs_edit != edit->yofs_edit) {
		edit->xofs_edit = new_xofs_edit;
		edit->yofs_edit = new_yofs_edit;
		return TRUE;
	}

	return FALSE;
}
