SureElec_string(Driver * drvthis, int x, int y, const char string[])
{
	PrivateData *p = drvthis->private_data;
	int i;


	x--;
	y--;


	if ((y < 0) || (y >= p->height))
		return;

	for (i = 0; (string[i] != '\0') && (x < p->width); i++, x++) {
		p->framebuf[(y * p->width) + x] = string[i];
	}
	debug(RPT_DEBUG, "SureElec: printed string at (%d,%d)", x, y);
}
