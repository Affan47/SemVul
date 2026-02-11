save_as_ppm(gchar *file,GdkPixbuf * pb)
{
  FILE *f;
  int  w= gdk_pixbuf_get_width(pb);
  int h= gdk_pixbuf_get_height(pb);

    if( gdk_pixbuf_get_n_channels(pb) != 3)  {
      show_error
	(g_strdup_printf
	 (  " cant save as .ppm :-( the image has %d channels",
	    gdk_pixbuf_get_n_channels(pb)  ));
      return FALSE;
    }

    f = fopen(file, "wb");
    if( f ==NULL)
      {
	showerr(file,_("\
the attempt to save the image file %s as produced error: %s"));
	return FALSE;
      }


    fprintf(f,"\
P6\n\
# CREATOR: " PACKAGE " " VERSION "\n\
%d %d\n\
255\n",
	    w,h);


    {
      guchar  *data = gdk_pixbuf_get_pixels(pb);
      int y, stride=gdk_pixbuf_get_rowstride(pb),
	channels=gdk_pixbuf_get_n_channels(pb);
      for (y=0;y<h;y++)
	if ( fwrite(data+y*stride, channels,w, f) != w)
	  {
	    showerr(file,_("\
the attempt to save the image file %s as produced error: %s"));
	  }
    }

    if( 0 != fclose (f))
      showerr(file,_("\
the attempt to close the saved image file %s as produced error: %s"));
    return TRUE;
}
