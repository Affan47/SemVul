gail_canvas_ref_child (AtkObject *obj,
                       gint i)
{
  GtkAccessible *accessible;
  GtkWidget *widget;
  GnomeCanvas *canvas;
  GnomeCanvasGroup *root_group;
  AtkObject *atk_object;


  if (i != 0)
    return NULL;
  g_return_val_if_fail (GAIL_IS_CANVAS (obj), NULL);

  accessible = GTK_ACCESSIBLE (obj);
  widget = gtk_accessible_get_widget (accessible);
  if (widget == NULL)

    return NULL;
  g_return_val_if_fail (GNOME_IS_CANVAS (widget), NULL);

  canvas = GNOME_CANVAS (widget);
  root_group = gnome_canvas_root (canvas);
  g_return_val_if_fail (root_group, NULL);

  atk_object = atk_gobject_accessible_for_object (G_OBJECT (root_group));
  g_object_ref (atk_object);
  return atk_object;
}
