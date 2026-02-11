putPixel(int x, int y, gColor col)
{
	guchar *p;
	unsigned int nchannels;
	unsigned int rowstride;
	GdkPixbuf *image;

	if ( (x<0) || (x>width()) ) return;
	if ( (y<0) || (y>height()) ) return;

  image = getPixbuf();

	nchannels=gdk_pixbuf_get_n_channels(image);
	rowstride=gdk_pixbuf_get_rowstride(image);

	p = gdk_pixbuf_get_pixels(image) + (x * nchannels) + (y * rowstride);


  p[0]=((col>>16) & 0xFF);
  p[1]=((col>>8) & 0xFF);
  p[2]=(col & 0xFF);
  if (nchannels>3) p[3]=255 - (col >> 24);

  invalidate();
}
