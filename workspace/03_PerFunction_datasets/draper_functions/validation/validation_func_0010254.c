keypress_cb (GtkWidget *win, GdkEventKey *event, gpointer data)
{
  GtkTreeIter iter;
  guint keyval = gdk_keyval_to_lower (event->keyval);
  guint state = event->state & GXINE_MODIFIER_MASK;

  if (gtk_tree_model_get_iter_first (kb_model, &iter))
  {
    do
    {
      key_binding_t *key_binding = lookup_binding (&iter);
      if (key_binding->state == state &&
	  (key_binding->keyval == keyval ||
	   key_binding->keyval == ~event->hardware_keycode))
      {
	char *binding = kb2str (key_binding);
	asreprintf (&binding, _("key binding %s"), binding);

	engine_queue_push (key_binding->cmd, NULL, NULL, NULL, NULL, binding);
	free (binding);
	return TRUE;
      }
    } while (gtk_tree_model_iter_next (kb_model, &iter));
  }


  if (data &&
      (gtk_accel_groups_activate (G_OBJECT (data), event->keyval, event->state)
       || gtk_bindings_activate_event (data, event)))
    return TRUE;


  if (win == app && menubar)
  {
    GtkWidget *toplevel = gtk_widget_get_toplevel (menubar);
    if (toplevel != app && GTK_WIDGET_VISIBLE (toplevel))
    {
      event->window = gtk_widget_get_toplevel (menubar)->window;
      event->send_event = TRUE;
      gtk_main_do_event ((GdkEvent *) event);
      return TRUE;
    }
  }

  if (keyval == GDK_Menu && state == 0)
  {
    do_popup:
    gtk_menu_popup (GTK_MENU(popup_menu), NULL, NULL, NULL, NULL, 0,
		    gtk_get_current_event_time ());
    return TRUE;
  }
  else if (is_menu_accel (win, event))
  {
    GtkWidget *toplevel = gtk_widget_get_toplevel (menubar);
    if (!menubar || !GTK_WIDGET_VISIBLE (toplevel == app ? menubar : toplevel))
      goto do_popup;
  }

  logprintf ("key_events: key %d not bound\n", event->keyval);

  return FALSE;
}
