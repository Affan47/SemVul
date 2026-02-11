gtk_plot_canvas_export_ps_with_size             (GtkPlotCanvas *canvas,
                                                 char *psname,
                                                 GtkPlotPageOrientation orient,
                                                 gboolean epsflag,
                                                 GtkPlotUnits units,
                                                 gint width,
                                                 gint height)
{
  GtkPlotPC *pc;
  GtkPlotPS *ps;
  gdouble scalex, scaley;
  gdouble m;
  GdkPixmap *pixmap;

  m = canvas->magnification;

  ps = GTK_PLOT_PS(gtk_plot_ps_new_with_size(psname, orient, epsflag,
                                             units,
                                             width, height,
                                             1.0 , 1.0));

  if(orient == GTK_PLOT_PORTRAIT){
    scalex = (gfloat)ps->page_width / (gfloat)canvas->width;
    scaley = (gfloat)ps->page_height / (gfloat)canvas->height;
  }else{
    scalex = (gfloat)ps->page_width / (gfloat)canvas->height;
    scaley = (gfloat)ps->page_height / (gfloat)canvas->width;
  }

  gtk_plot_ps_set_scale(ps, scalex, scaley);

  pc = canvas->pc;
  canvas->pc = GTK_PLOT_PC(ps);

  pixmap = canvas->pixmap;
  canvas->pixmap = NULL;
  gtk_plot_canvas_set_magnification(canvas, 1.0);
  gtk_plot_canvas_paint(canvas);
  gtk_plot_canvas_set_magnification(canvas, m);
  gdk_pixmap_unref(canvas->pixmap);
  canvas->pixmap = pixmap;

  canvas->pc = pc;

  gtk_object_destroy(GTK_OBJECT(ps));

  return TRUE;
}
