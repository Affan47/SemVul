glade_placeholder_drag_drop (_GladeDrag *dest, gint x, gint y, GObject *data)
{
  GladePlaceholder *placeholder = GLADE_PLACEHOLDER (dest);
  GladeWidget *gsource;

  if (!data)
    return FALSE;

  if (GLADE_IS_WIDGET_ADAPTOR (data))
    {
      GladeWidget *parent = glade_placeholder_get_parent (placeholder);

      glade_command_create (GLADE_WIDGET_ADAPTOR (data), parent, placeholder,
                            glade_widget_get_project (parent));
      return TRUE;
    }
  else if ((gsource = glade_widget_get_from_gobject (data)))
    {
      GladeWidget *parent = glade_placeholder_get_parent (placeholder);
      GList widgets = {gsource, NULL, NULL};


      if (parent != gsource)
        {
          glade_command_dnd (&widgets, parent, placeholder);
          return TRUE;
        }
    }

  return FALSE;
}
