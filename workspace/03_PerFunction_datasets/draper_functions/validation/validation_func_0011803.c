update_title(const char *filename, MainWin *mw )
{
    static char fname[50];
    static int wid, hei;

    char buf[100];

    if(filename != NULL)
    {
      strncpy(fname, filename, 49);
      fname[49] = '\0';

      wid = gdk_pixbuf_get_width( mw->pix );
      hei = gdk_pixbuf_get_height( mw->pix );
    }

    snprintf(buf, 100, "%s (%dx%d) %d%%", fname, wid, hei, (int)(mw->scale * 100));
    gtk_window_set_title( (GtkWindow*)mw, buf );

    return;
}
