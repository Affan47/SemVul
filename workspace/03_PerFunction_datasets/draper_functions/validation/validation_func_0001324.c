StoreCmap1(PLStream *pls)
{
    XwDev *dev = (XwDev *) pls->dev;
    XwDisplay *xwd = (XwDisplay *) dev->xwd;

    PLColor cmap1color;
    int i;

    if ( ! xwd->color)
	return;

    for (i = 0; i < xwd->ncol1; i++) {
	plcol_interp(pls, &cmap1color, i, xwd->ncol1);
	PLColor_to_XColor(&cmap1color, &xwd->cmap1[i]);
	if (xwd->rw_cmap)
	  XStoreColor(xwd->display, xwd->map, &xwd->cmap1[i]);
	else
	  XAllocColor(xwd->display, xwd->map, &xwd->cmap1[i]);
    }
}
