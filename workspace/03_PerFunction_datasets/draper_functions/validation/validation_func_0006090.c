display_put(struct display *display, int row, int column,
		 Unicode_t unicode, rgba_t fgrgba, rgba_t bgrgba)
{
	char buf[8];
	struct cell *cell;
	if (row < 0 || row >= display->rows ||
	    column < 0 || column >= display->columns)
		return;
	if (unicode < ' ')
		unicode = ' ';
	cell = &display->image[row*display->columns + column];
	if (cell->unicode == unicode &&
	    (cell->fgrgba == fgrgba || unicode == ' ') &&
	    cell->bgrgba == bgrgba)
		return;
	moveto(display, row, column);
	background_color(display, bgrgba);
	if (unicode != ' ')
		foreground_color(display, fgrgba);
	out(display, buf, unicode_utf8(buf, unicode));
	display->at_column++;

	cell = &display->image[row*display->columns + column];
	cell->unicode = unicode;
	cell->bgrgba = bgrgba;
	cell->fgrgba = fgrgba;
}
