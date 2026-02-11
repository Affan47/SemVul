gtk_plot3d_destroy (GtkObject *object)
{
  GtkPlot3D *plot = GTK_PLOT3D(object);
  gtk_psfont_unref();

  if (plot->xy)
    gtk_object_unref(GTK_OBJECT(plot->xy));
  if (plot->xz)
    gtk_object_unref(GTK_OBJECT(plot->xz));
  if (plot->yx)
    gtk_object_unref(GTK_OBJECT(plot->yx));
  if (plot->yz)
    gtk_object_unref(GTK_OBJECT(plot->yz));
  if (plot->zx)
    gtk_object_unref(GTK_OBJECT(plot->zx));
  if (plot->zy)
    gtk_object_unref(GTK_OBJECT(plot->zy));

  if ( GTK_OBJECT_CLASS (parent_class)->destroy )
    (* GTK_OBJECT_CLASS (parent_class)->destroy) (object);
}
