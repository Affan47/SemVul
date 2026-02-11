bonobo_dock_item_grab_pointer (BonoboDockItem *item)
{
  GdkCursor *fleur;
  GdkWindow *gdk_window;

  g_assert (BONOBO_IS_DOCK_ITEM (item));

  item->in_drag = TRUE;

  fleur = gdk_cursor_new_for_display
	  (gtk_widget_get_display (GTK_WIDGET (item)),
	   GDK_FLEUR);

  if (item->is_floating) {


        gdk_window = GTK_WIDGET (item->_priv->float_window)->window;
  } else  {
        gdk_window = item->bin_window;
  }

  while (gdk_pointer_grab (gdk_window,
                           FALSE,
                           (GDK_BUTTON1_MOTION_MASK |
                            GDK_POINTER_MOTION_HINT_MASK |
                            GDK_BUTTON_RELEASE_MASK),
                           NULL,
                           fleur,
                           GDK_CURRENT_TIME) != 0);


  gdk_cursor_unref (fleur);
}
